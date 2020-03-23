#include "MainMenuState.h"
#include "GameState.h"
#include "HighScoreState.h"

MainMenuState::MainMenuState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	playButton(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
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
	CheckButtonClick();
}

void MainMenuState::HandleInput(const sf::Event& event)
{
}

void MainMenuState::Update(float dt)
{
}

void MainMenuState::Draw()
{
	gameData->window.clear();
	playButton.Draw(gameData->window);
	highScoresBtn.Draw(gameData->window);
	gameData->window.display();
}

void MainMenuState::SetupButtons(const sf::Font& font)
{
	playButton.SetFont(font, CHARACTER_SIZE);
	playButton.SetTextColor(GREEN);
	playButton.SetOutline(GREEN, OUTLINE_THICKNESS);
	playButton.SetContent("Play", Alignment::CENTER);

	highScoresBtn.SetFont(font, CHARACTER_SIZE);
	highScoresBtn.SetTextColor(GREEN);
	highScoresBtn.SetOutline(GREEN, OUTLINE_THICKNESS);
	highScoresBtn.SetContent("High Scores", Alignment::CENTER);
}

void MainMenuState::CheckButtonHover()
{
	bool isHovering = gameData->input.IsHovering(playButton.GetRect(), gameData->window);
	playButton.MouseHoverEffect(isHovering);
	isHovering = gameData->input.IsHovering(highScoresBtn.GetRect(), gameData->window);
	highScoresBtn.MouseHoverEffect(isHovering);
}

void MainMenuState::CheckButtonClick()
{
	bool isClicked = gameData->input.IsRectClicked(playButton.GetRect(), sf::Mouse::Left, gameData->window);
	if (isClicked)
	{
		gameData->machine.AddState(std::make_unique<GameState>(gameData));
	}
	isClicked = gameData->input.IsRectClicked(highScoresBtn.GetRect(), sf::Mouse::Left, gameData->window);
	if (isClicked)
	{
		gameData->machine.AddState(std::make_unique<HighScoreState>(gameData));
	}
}

void MainMenuState::SetGuiElementPositions()
{
	playButton.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	playButton.CenterText();

	auto playBtnPos = playButton.GetPosition();
	highScoresBtn.SetPosition(playBtnPos.x, playBtnPos.y + playButton.GetRect().height + margin);

}
