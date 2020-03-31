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
	auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	highScores.Load();
	highScores.SetupTop10List(font);
	SetupButtons(font);
	SetGuiElementPositions();
}

void HighScoreState::HandleInput()
{
	CheckButtonHover();
}

void HighScoreState::HandleInput(const sf::Event& event)
{
	CheckButtonClick(event);
}

void HighScoreState::Update(float dt)
{
}

void HighScoreState::Draw()
{
	gameData->window.clear();
	backBtn.Draw(gameData->window);
	highScores.Draw(gameData->window);
	gameData->window.display();
}


void HighScoreState::CheckButtonHover()
{
	bool isHovering = gameData->input.IsHovering(backBtn.GetRect(), gameData->window);
	backBtn.MouseHoverEffect(isHovering);
}

void HighScoreState::CheckButtonClick(const sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (gameData->input.IsRectClicked(backBtn.GetRect(), gameData->window))
		{
			gameData->machine.AddState(std::make_unique<MainMenuState>(gameData));
		}
	}
}

void HighScoreState::SetupButtons(const sf::Font& font)
{
	backBtn.SetTemplate(font, "Back");
}

void HighScoreState::SetGuiElementPositions()
{
	backBtn.SetPosition({ WINDOW_WIDTH - backBtn.GetRect().width, 0 });
	highScores.SetGuiElementPositions();
}
