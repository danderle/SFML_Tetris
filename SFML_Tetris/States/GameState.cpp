#include "GameState.h"

GameState::GameState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	field({0,0})
{
}

void GameState::Init()
{
}

void GameState::HandleInput()
{
}

void GameState::Update(float dt)
{
}

void GameState::Draw()
{
	gameData->window.clear();
	field.Draw(gameData->window);
	gameData->window.display();
}
