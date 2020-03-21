#include "SplashState.h"
#include "MainMenuState.h"

SplashState::SplashState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData)
{
}

void SplashState::Init()
{
	gameData->assets.LoadTexture(splashScreenTexture, SPLASH_SCREEN_PATH);
	splashScreenSprite.setTexture(gameData->assets.GetTexture(splashScreenTexture));
	float width = splashScreenSprite.getGlobalBounds().width;
	float height = splashScreenSprite.getGlobalBounds().height;
	splashScreenSprite.setPosition(WINDOW_WIDTH / 2 - width / 2, WINDOW_HEIGHT / 2 - height / 2);
}

void SplashState::HandleInput()
{
}

void SplashState::HandleInput(sf::Event event)
{
}

void SplashState::Update(float dt)
{
	timePassed += dt;
	if (timePassed > displayTime)
	{
		gameData->machine.AddState(std::make_unique<MainMenuState>(gameData));
	}
}

void SplashState::Draw()
{
	gameData->window.clear();
	gameData->window.draw(splashScreenSprite);
	gameData->window.display();
}
