#include "HighScoreState.h"
#include "MainMenuState.h"

HighScoreState::HighScoreState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	backBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT)
{
}

void HighScoreState::Init()
{
	LoadHighScores();
	auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	SetupHighScoreTexts(font);
	SetupButtons(font);
	SetGuiElementPositions();
}

void HighScoreState::HandleInput()
{
	CheckButtonHover();
	CheckButtonClick();
}

void HighScoreState::HandleInput(const sf::Event& event)
{
}

void HighScoreState::Update(float dt)
{
}

void HighScoreState::Draw()
{
	gameData->window.clear();
	backBtn.Draw(gameData->window);
	gameData->window.draw(top10Text);
	for (auto text : highScoreTexts)
	{
		gameData->window.draw(text);
	}
	gameData->window.display();
}

void HighScoreState::LoadHighScores()
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

void HighScoreState::CheckButtonHover()
{
	bool isHovering = gameData->input.IsHovering(backBtn.GetRect(), gameData->window);
	backBtn.MouseHoverEffect(isHovering);
}

void HighScoreState::CheckButtonClick()
{
	bool isClicked = gameData->input.IsRectClicked(backBtn.GetRect(), sf::Mouse::Left, gameData->window);
	if (isClicked)
	{
		gameData->machine.AddState(std::make_unique<MainMenuState>(gameData));
	}
}

void HighScoreState::SetupHighScoreTexts(const sf::Font& font)
{
	sf::Text text;
	text.setFont(font);
	text.setFillColor(RED);
	unsigned int max = 0;
	for (auto& score : highScores)
	{
		std::string number = std::to_string(score.second);
		max = max < number.size() ? number.size() : max;
		std::string spacer = "";
		unsigned int diff = max - number.size();
		while (spacer.size() <= diff)
		{
			spacer.push_back(' ');
		}
		std::string setString = score.first + "                " + spacer + number;
		text.setString(setString);
		highScoreTexts.push_back(text);
	}
	top10Text.setFont(font);
	top10Text.setFillColor(RED);
	top10Text.setString("Top 10");
}

void HighScoreState::SetupButtons(const sf::Font& font)
{
	backBtn.SetTemplate(font, "Back");
}

void HighScoreState::SetGuiElementPositions()
{
	backBtn.SetPosition({ WINDOW_WIDTH - backBtn.GetRect().width, 0 });
	float yStartPosition = WINDOW_HEIGHT / 7;
	float padding = 20.f;
	float width = top10Text.getGlobalBounds().width;
	top10Text.setPosition((WINDOW_WIDTH - width) / 2, yStartPosition);
	yStartPosition = yStartPosition + top10Text.getCharacterSize() + padding;
	float xStartPosition = highScoreTexts.size() > 0 ? (WINDOW_WIDTH - highScoreTexts[0].getLocalBounds().width) / 2 : 0;
	for (unsigned int i = 0; i < highScoreTexts.size(); i++)
	{
		float yNextPosition = (i * highScoreTexts[i].getCharacterSize()) + padding * (i + 1);
		highScoreTexts[i].setPosition(xStartPosition, yStartPosition + yNextPosition);
	}
}
