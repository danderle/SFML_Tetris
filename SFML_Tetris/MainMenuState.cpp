#include "MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData)
{
}

void MainMenuState::Init()
{
}

void MainMenuState::HandleInput()
{
}

void MainMenuState::Update(float dt)
{
}

void MainMenuState::Draw()
{
	gameData->window.clear();
	gameData->window.display();
}
