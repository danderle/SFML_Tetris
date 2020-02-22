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
};

