#include "MainMenuState.h"
#include "GameState.h"
#include "SettingsState.h"
#include "HighScoreState.h"

MainMenuState::MainMenuState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	playButton(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	settingsBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	highScoresBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT)
{
}

void MainMenuState::Init()
{
	const auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	SetupButtons(font);
	SetGuiElementPositions();
}

void MainMenuState::HandleInput()
{
	CheckButtonHover();
}

void MainMenuState::HandleInput(const sf::Event& event)
{
	CheckButtonClick(event);
}

void MainMenuState::Update(float dt)
{
}

void MainMenuState::Draw()
{
	gameData->window.clear();
	playButton.Draw(gameData->window);
	settingsBtn.Draw(gameData->window);
	highScoresBtn.Draw(gameData->window);
	gameData->window.display();
}

void MainMenuState::SetupButtons(const sf::Font& font)
{
	playButton.SetTemplate(font, "Play");
	settingsBtn.SetTemplate(font, "Settings");
	highScoresBtn.SetTemplate(font, "High Scores");
}

void MainMenuState::CheckButtonHover()
{
	bool isHovering = gameData->input.IsHovering(playButton.GetRect(), gameData->window);
	playButton.MouseHoverEffect(isHovering);
	isHovering = gameData->input.IsHovering(settingsBtn.GetRect(), gameData->window);
	settingsBtn.MouseHoverEffect(isHovering);
	isHovering = gameData->input.IsHovering(highScoresBtn.GetRect(), gameData->window);
	highScoresBtn.MouseHoverEffect(isHovering);
}

void MainMenuState::CheckButtonClick(const sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (gameData->input.IsRectClicked(playButton.GetRect(), gameData->window))
		{
			gameData->machine.AddState(std::make_unique<GameState>(gameData));
		}
		else if (gameData->input.IsRectClicked(settingsBtn.GetRect(), gameData->window))
		{
			gameData->machine.AddState(std::make_unique<SettingsState>(gameData));
		}
		else if (gameData->input.IsRectClicked(highScoresBtn.GetRect(), gameData->window))
		{
			gameData->machine.AddState(std::make_unique<HighScoreState>(gameData));
		}
	}
}

void MainMenuState::SetGuiElementPositions()
{
	playButton.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3 });
	playButton.CenterText();

	auto previousBtnPos = playButton.GetPosition();
	settingsBtn.SetPosition(previousBtnPos.x, previousBtnPos.y + playButton.GetRect().height + margin);

	previousBtnPos = settingsBtn.GetPosition();
	highScoresBtn.SetPosition(previousBtnPos.x, previousBtnPos.y + settingsBtn.GetRect().height + margin);

}
