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
	for (auto& score : highScores)
	{
		sf::Text text;
		text.setFont(font);
		text.setFillColor(RED);
		std::string setString = score.first + "                     " + std::to_string(score.second);
		text.setString(setString);
		highScoreTexts.push_back(text);
	}
}

void HighScoreState::SetupButtons(const sf::Font& font)
{
	backBtn.SetFont(font, CHARACTER_SIZE);
	backBtn.SetTextColor(GREEN);
	backBtn.SetOutline(GREEN, OUTLINE_THICKNESS);
	backBtn.SetContent("Back", Alignment::CENTER);
}

void HighScoreState::SetGuiElementPositions()
{
	backBtn.SetPosition({ WINDOW_WIDTH - backBtn.GetRect().width, 0 });
	float yStartPosition = WINDOW_HEIGHT / 4;
	float padding = 20.f;
	for (unsigned int i = 0; i < highScoreTexts.size(); i++)
	{
		float yNextPosition = (i * highScoreTexts[i].getCharacterSize()) + padding * (i + 1);
		highScoreTexts[i].setPosition((WINDOW_WIDTH - highScoreTexts[i].getLocalBounds().width) / 2, yStartPosition + yNextPosition);
	}
}
