#include "GameOverState.h"
#include "MainMenuState.h"
#include <sstream>
GameOverState::GameOverState(std::shared_ptr<GameData> _gameData, const unsigned int _newScore)
:
	gameData(_gameData),
	gameOverTxtBox(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	newGameBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	newScore(_newScore)
{
}

void GameOverState::Init()
{
	LoadHighScores();
	SetNewHighScore();
	auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	SetupTextBoxes(font);
	SetupHighScoreTexts(font);
	SetupButtons(font);
	SetGuiElementPositions();
}

void GameOverState::HandleInput()
{
	CheckButtonHover();
	CheckButtonClick();
}

void GameOverState::HandleInput(const sf::Event& event)
{
	if(saveNewScore)
	{
		std::string scoreText = scoreTexts[newScoreIndex].getString();
		if (!scoreHolderSet && scoreHolder.size() < 3 && event.KeyReleased && event.key.code >= 0 && event.key.code < 27)
		{
			scoreHolder.push_back(letters[event.key.code]);
			for (unsigned int i = 0; i < scoreHolder.size(); i++)
			{
				scoreText[i] = scoreHolder[i];
			}
			if (scoreHolder.size() < 3)
			{
				scoreText[scoreHolder.size()] = '_';
			}
			scoreTexts[newScoreIndex].setString(scoreText);
		}
		else if (!scoreHolderSet && gameData->input.KeyReleased(event, sf::Keyboard::Backspace))
		{
			if (scoreHolder.size() != 0)
			{
				scoreHolder.pop_back();
				if (scoreHolder.size() < 3)
				{
					scoreText[scoreHolder.size()] = '_';
					scoreText[scoreHolder.size() + 1] = ' ';
				}
				scoreTexts[newScoreIndex].setString(scoreText);
			}
		}
		else if (!scoreHolderSet && gameData->input.KeyReleased(event, sf::Keyboard::Enter))
		{
			scoreHolderSet = true;
			highScores[newScoreIndex].first = scoreHolder;
			std::ofstream outStream("HighScores.txt");
			for (auto highScore : highScores)
			{
				highScore.first = highScore.first.empty() ? "XXX" : highScore.first;
				outStream << highScore.first << " " << std::to_string(highScore.second) << std::endl;
			}
			outStream.close();
			newGameBtn.Enable();
		}
	}
}

void GameOverState::Update(float dt)
{
	lastFlash += dt;
	if (saveNewScore && (lastFlash > flashTime))
	{
		
		lastFlash = 0;
		if (!scoreHolderSet && switchColor)
		{
			scoreTexts[newScoreIndex].setFillColor(TRANSPARENT);
		}
		else
		{
			scoreTexts[newScoreIndex].setFillColor(RED);
		}
		switchColor = !switchColor;
	}
}

void GameOverState::Draw()
{
	  
	gameData->window.clear();
	newGameBtn.Draw(gameData->window);
	gameOverTxtBox.Draw(gameData->window);
	gameData->window.draw(top10Text);
	for (auto text : scoreTexts)
	{
		gameData->window.draw(text);
	}
	gameData->window.display();
}

//// **** Private Functions ****

void GameOverState::SetupButtons(const sf::Font& font)
{
	newGameBtn.SetTemplate(font, "Main Menu");
}

void GameOverState::SetupTextBoxes(const sf::Font& font)
{
	gameOverTxtBox.SetFont(font, CHARACTER_SIZE);
	gameOverTxtBox.SetContent("GAME OVER", Alignment::CENTER);
	gameOverTxtBox.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	gameOverTxtBox.SetTextColor(BLACK);
	gameOverTxtBox.SetOutlineColor(BLACK, OUTLINE_THICKNESS);
}


void GameOverState::CheckButtonHover()
{
	newGameBtn.MouseHoverEffect(gameData->input.IsHovering(newGameBtn.GetRect(), gameData->window));
}

void GameOverState::CheckButtonClick()
{
	if (newGameBtn.IsEnabled() &&
		gameData->input.IsRectClicked(newGameBtn.GetRect(), sf::Mouse::Left, gameData->window))
	{
		gameData->machine.AddState(std::make_unique<MainMenuState>(gameData));
	}
}

void GameOverState::SetGuiElementPositions()
{
	gameOverTxtBox.SetPosition({ (WINDOW_WIDTH - TEXTBOX_WIDTH) / 2, TEXTBOX_HEIGHT });

	float padding = 20.f;
	float yStartPosition = gameOverTxtBox.GetPosition().y + gameOverTxtBox.GetRect().height + padding;
	top10Text.setPosition((WINDOW_WIDTH - top10Text.getGlobalBounds().width) / 2, yStartPosition);
	yStartPosition = yStartPosition + top10Text.getCharacterSize() + padding;
	float xStartPosition = scoreTexts.size() > 0 ? (WINDOW_WIDTH - scoreTexts[0].getLocalBounds().width) / 2 : 0;
	for (unsigned int i = 0; i < scoreTexts.size(); i++)
	{
		float yNextPosition = (i * scoreTexts[i].getCharacterSize()) + padding * (i + 1);
		scoreTexts[i].setPosition(xStartPosition, yStartPosition + yNextPosition);
	}
	yStartPosition = scoreTexts.back().getPosition().y + scoreTexts.back().getLocalBounds().height + padding * 2;

	newGameBtn.SetPosition({ gameOverTxtBox.GetPosition().x, yStartPosition });
}

void GameOverState::LoadHighScores()
{
	std::ifstream inputStream(HIGHSCORE_PATH);
	std::string line;
	while (std::getline(inputStream, line).good() && !line.empty())
	{
		std::stringstream ss;
		ss << line;
		std::string name;
		unsigned int score = 0;
		ss >> name;
		ss >> score;
		while (name.size() < 3)
		{
			name.push_back(' ');
		}
		highScores.emplace_back(name, score);
	}
	inputStream.close();
}

void GameOverState::SetNewHighScore()
{
	unsigned int index = 0;
	for (auto& score : highScores)
	{
		if (newScore > score.second)
		{
			break;
		}
		index++;
	}
	if (index < maxHighScoresSize)
	{
		scoreSet = true;
		saveNewScore = true;
		newGameBtn.Disable();
		auto it = highScores.begin() + index;
		highScores.insert(it, { "_  ", newScore });
		newScoreIndex = index;
	}
}

void GameOverState::SetupHighScoreTexts(const sf::Font& font)
{
	sf::Text text;
	text.setFont(font);
	text.setFillColor(RED);
	unsigned int max = 0;
	for (unsigned int i = 0; i < 10 && i < highScores.size(); i++)
	{
		std::string number = std::to_string(highScores[i].second);
		max = max < number.size() ? number.size() : max;
		std::string spacer = "";
		unsigned int diff = max - number.size();
		while (spacer.size() <= diff)
		{
			spacer.push_back(' ');
		}
		std::string setString = highScores[i].first + "                " + spacer + number;
		text.setString(setString);
		scoreTexts.push_back(text);
	}
	top10Text.setFont(font);
	top10Text.setFillColor(RED);
	top10Text.setString("Top 10");
}