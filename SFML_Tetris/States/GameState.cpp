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
	if (manualTimePassed > manualMoveTime)
	{
		if (gameData->input.KeyHit(sf::Keyboard::Key::Left))
		{
			manualTimePassed = 0;
			if (field.CanMoveLeft(*tetrimino))
			{
				tetrimino->MoveLeft();
			}
		}
		if (gameData->input.KeyHit(sf::Keyboard::Key::Right))
		{
			manualTimePassed = 0;
			if (field.CanMoveRight(*tetrimino))
			{
				tetrimino->MoveRight();
			}
		}
		if (gameData->input.KeyHit(sf::Keyboard::Key::Down))
		{
			manualTimePassed = 0;
			tetrimino->MoveDown();
		}
		if (gameData->input.KeyHit(sf::Keyboard::Key::A))
		{

		}
		else if (gameData->input.KeyHit(sf::Keyboard::Key::D))
		{

		}
	}
}

void GameState::Update(float dt)
{
	manualTimePassed += dt;
	autoTimePassed += dt;
	if (autoTimePassed > autoMoveTime)
	{
		autoTimePassed = 0;
		tetrimino->MoveDown();
	}
	field.ShowOnField(*tetrimino);
	if (tetrimino->IsPlacedOnField())
	{
		tetrimino = std::move(nextTetrimino);
		nextTetrimino = std::make_unique<Tetrimino>(tetri, sf::Color::Blue);
	}
}

void GameState::Draw()
{
	gameData->window.clear();
	field.Draw(gameData->window);
	gameData->window.display();
}
