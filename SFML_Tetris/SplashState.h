#pragma once 
#include "Game.h"
#include "State.h"

class SplashState : public State
{
public:
	SplashState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	std::shared_ptr<GameData> gameData;
	std::string  test = "Test";
};

