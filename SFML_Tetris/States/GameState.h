#pragma once
#include "Game.h"
#include "State.h"
#include "Field.h"

class GameState : public State
{
public:
	GameState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	std::shared_ptr<GameData> gameData;
	Field field;
	std::unique_ptr<Tetrimino> tetrimino;
	float timePassed = 0;
	static constexpr float moveTime = 0.5f;
};

