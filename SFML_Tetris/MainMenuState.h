#pragma once
#include "Game.h"
#include "State.h"
#include "Button.h"
class MainMenuState : public State
{
public:
	MainMenuState() = delete;
	MainMenuState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	std::shared_ptr<GameData> gameData;
	Button playButton;
};

