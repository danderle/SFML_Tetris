#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	playButton(TEXTBOX_WIDTH, TEXTBOX_HEIGHT)
{
}

void MainMenuState::Init()
{
	const auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	playButton.SetFont(font, CHARACTER_SIZE);
	playButton.SetTextColor(GREEN);
	playButton.SetOutline(GREEN, OUTLINE_THICKNESS);
	playButton.SetContent("Play", Alignment::CENTER);
	playButton.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
	playButton.CenterText();
}

void MainMenuState::HandleInput()
{
	bool isHovering = gameData->input.IsHovering(playButton.GetRect(), gameData->window);
	playButton.MouseHoverEffect(isHovering);
	bool isClicked = gameData->input.IsRectClicked(playButton.GetRect(), sf::Mouse::Left, gameData->window);
	if (isClicked)
	{
		gameData->machine.AddState(std::make_unique<GameState>(gameData));
	}
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
	gameData->window.display();
}
