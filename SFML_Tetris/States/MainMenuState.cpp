#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	playButton(250, 50)
{
}

void MainMenuState::Init()
{
	gameData->assets.LoadFont(ROBOT_FONT, ROBOTO_FONT_PATH);
	const auto& font = gameData->assets.GetFont(ROBOT_FONT);
	playButton.SetFont(font);
	playButton.SetContent("Play");
	playButton.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
	playButton.CenterText();
}

void MainMenuState::HandleInput()
{
	bool isHovering = gameData->input.IsHovering(playButton.GetRect(), gameData->window);
	playButton.MouseHover(isHovering);
	bool isClicked = gameData->input.IsRectClicked(playButton.GetRect(), sf::Mouse::Left, gameData->window);
	if (isClicked)
	{
		gameData->machine.AddState(std::make_unique<GameState>(gameData));
	}
}

void MainMenuState::HandleInput(sf::Event event)
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
