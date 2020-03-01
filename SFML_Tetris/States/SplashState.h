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
	void HandleInput(sf::Event event);
	void Update(float dt);
	void Draw();

private:
	const std::string splashScreenTexture = "Splash";
	static constexpr int displayTime = 0;

	float timePassed = 0.f;

	std::shared_ptr<GameData> gameData;
	std::string  test = "Test";
	sf::Sprite splashScreenSprite;
};

