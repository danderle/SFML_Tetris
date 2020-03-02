#include "GameState.h"

//// initialize TetriminoFactory one time
TetriminoFactory GameState::factory;

GameState::GameState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	field({30,0})
{
}

void GameState::Init()
{
	tetrimino = factory.CreateTetrimino();
	nextTetrimino = factory.CreateTetrimino();
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
			autoTimePassed = 0;
			MoveTetriminoOrPlaceOnField();

		}
	}
}

void GameState::HandleInput(sf::Event event)
{
	if (event.key.code == sf::Keyboard::A)
	{
		tetrimino->RotateLeft();
		if (!field.CanRotate(*tetrimino))
		{
			tetrimino->RotateRight();
		}
	}
	else if (event.key.code == sf::Keyboard::D)
	{
		tetrimino->RotateRight();
		if (!field.CanRotate(*tetrimino))
		{
			tetrimino->RotateLeft();
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
		MoveTetriminoOrPlaceOnField();
	}
	field.ShowOnField(*tetrimino);
	field.ClearFullRows();
}

void GameState::Draw()
{
	gameData->window.clear();
	field.Draw(gameData->window);
	gameData->window.display();
}


//// **** Private Functions ****

void GameState::MoveTetriminoOrPlaceOnField()
{
	if (field.CanMoveDown(*tetrimino))
	{
		tetrimino->MoveDown();
	}
	else
	{
		field.ClearFieldAndSaveLastPosition();
		field.PlaceLastPositionOnField(tetrimino->GetColor());
		tetrimino = std::move(nextTetrimino);
		nextTetrimino = factory.CreateTetrimino();
	}
}
