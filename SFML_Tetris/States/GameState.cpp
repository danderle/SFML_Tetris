#include "GameState.h"

GameState::GameState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	field({0,0})
{
}

void GameState::Init()
{
	tetrimino = std::make_unique<Tetrimino>(tetri, sf::Color::Blue);
	nextTetrimino = std::make_unique<Tetrimino>(tetri, sf::Color::Blue);
}

void GameState::HandleInput()
{
}

void GameState::Update(float dt)
{
	timePassed += dt;
	if (timePassed > moveTime)
	{
		timePassed = 0;
		tetrimino->MoveDown();
		field.ShowOnField(*tetrimino);
		if (tetrimino->IsPlacedOnField())
		{
			tetrimino = std::move(nextTetrimino);
			nextTetrimino = std::make_unique<Tetrimino>(tetri, sf::Color::Blue);
		}
	}
}

void GameState::Draw()
{
	gameData->window.clear();
	field.Draw(gameData->window);
	gameData->window.display();
}
