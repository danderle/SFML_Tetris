#pragma once 
#include "Game.h"
#include "State.h"

class SplashState : public State
{
public:
	SplashState() = delete;
	SplashState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void HandleInput(const sf::Event& event);
	void Update(float dt);
	void Draw();

private:
	std::shared_ptr<GameData> gameData;
	sf::Sprite splashScreenSprite;
};

