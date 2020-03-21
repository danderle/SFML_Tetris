#include "GameOverState.h"
#include "GameState.h"
#include <sstream>
GameOverState::GameOverState(std::shared_ptr<GameData> _gameData, const unsigned int newScore)
:
	gameData(_gameData),
	gameOverTxtBox(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	newGameBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT)
{
	auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	gameOverTxtBox.SetPosition({ (WINDOW_WIDTH - TEXTBOX_WIDTH) / 2, TEXTBOX_HEIGHT });
	gameOverTxtBox.SetFont(font, CHARACTER_SIZE);
	gameOverTxtBox.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	gameOverTxtBox.SetContent("GAME OVER", Alignment::CENTER);
	gameOverTxtBox.SetTextColor(BLACK);
	gameOverTxtBox.SetOutline(BLACK, OUTLINE_THICKNESS);

	
	
	std::string filename = "HighScores.txt";
	std::ifstream inputStream(filename);
	std::string line;
	while (std::getline(inputStream, line).good() && !line.empty())
	{
		std::stringstream ss;
		ss << line;
		std::string name;
		unsigned int score = 0;
		ss >> name;
		ss >> score;
		if (!scoreSet && score < newScore)
		{
			scoreSet = true;
			highScores.emplace_back("_  ", newScore);
			newScoreindex = highScores.size() - 1;
		}
		highScores.emplace_back(name, score);
	}
	inputStream.close();
	if (!scoreSet && highScores.size() < 10)
	{
		highScores.emplace_back("_  ", newScore);
		newScoreindex = highScores.size() - 1;
	}

	float yStartPosition = gameOverTxtBox.GetPosition().y + gameOverTxtBox.GetRect().height;
	for (unsigned int i = 0; i < 10 && i < highScores.size(); i++)
	{
		float padding = 20.f;
		sf::Text text;
		text.setFont(font);
		text.setFillColor(RED);
		std::string setString = highScores[i].first + "                     " + std::to_string(highScores[i].second);
		text.setString(setString);
		float yNextPosition = (i * text.getCharacterSize()) + padding * (i + 1);
		text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, yStartPosition + yNextPosition);
		scoreTexts.push_back(text);
	}
	
	yStartPosition = scoreTexts.back().getPosition().y + scoreTexts.back().getLocalBounds().height + 20;
	newGameBtn.SetFont(font, CHARACTER_SIZE);
	newGameBtn.SetOutline(GREEN, OUTLINE_THICKNESS);
	newGameBtn.SetContent("NEW GAME", Alignment::CENTER);
	newGameBtn.SetTextColor(GREEN);
	newGameBtn.SetPosition({ gameOverTxtBox.GetPosition().x, yStartPosition });
}

void GameOverState::Init()
{
}

void GameOverState::HandleInput()
{
	newGameBtn.MouseHoverEffect(gameData->input.IsHovering(newGameBtn.GetRect(), gameData->window));
	if (gameData->input.IsRectClicked(newGameBtn.GetRect(), sf::Mouse::Left, gameData->window))
	{
		gameData->machine.AddState(std::make_unique<GameState>(gameData));
	}
}

void GameOverState::HandleInput(sf::Event event)
{
	std::string scoreText = scoreTexts[newScoreindex].getString();
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
		scoreTexts[newScoreindex].setString(scoreText);
	}
	else if (!scoreHolderSet && gameData->input.KeyReleased(event, sf::Keyboard::Backspace))
	{
		if (scoreHolder.size() != 0)
		{
			scoreHolder.pop_back();
			if (scoreHolder.size() < 3)
			{
				scoreText[scoreHolder.size()] = '_';
				scoreText[scoreHolder.size()+1] = ' ';
			}
			scoreTexts[newScoreindex].setString(scoreText);
		}
	}
	else if (!scoreHolderSet && gameData->input.KeyReleased(event, sf::Keyboard::Enter))
	{
		scoreHolderSet = true;
		highScores[newScoreindex].first = scoreHolder;
		std::ofstream outStream("HighScores.txt");
		for (auto highScore : highScores)
		{
			outStream << highScore.first << " " << std::to_string(highScore.second) << std::endl;
		}
		outStream.close();
	}
}

void GameOverState::Update(float dt)
{
	lastFlash += dt;
	if (lastFlash > flashTime)
	{
		lastFlash = 0;
		if (!scoreHolderSet && switchColor)
		{
			scoreTexts[newScoreindex].setFillColor(TRANSPARENT);
			switchColor = false;
		}
		else
		{
			scoreTexts[newScoreindex].setFillColor(RED);
			switchColor = true;
		}
	}
}

void GameOverState::Draw()
{
	gameData->window.clear();
	newGameBtn.Draw(gameData->window);
	gameOverTxtBox.Draw(gameData->window);
	for (auto text : scoreTexts)
	{
		gameData->window.draw(text);
	}
	gameData->window.display();
}
