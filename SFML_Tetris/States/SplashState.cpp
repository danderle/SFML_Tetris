#include "SplashState.h"
#include "MainMenuState.h"

SplashState::SplashState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData)
{
}

void SplashState::Init()
{
	splashScreenSprite.setTexture(gameData->assets.GetTexture(SPLASH_SCREEN));
	float width = splashScreenSprite.getGlobalBounds().width;
	float height = splashScreenSprite.getGlobalBounds().height;
	splashScreenSprite.setPosition(WINDOW_WIDTH / 2 - width / 2, WINDOW_HEIGHT / 2 - height / 2);
	gameData->assets.GetSound(SPLASH_SOUND).play();
}

void SplashState::HandleInput()
{
}

void SplashState::HandleInput(const sf::Event& event)
{
}

void SplashState::Update(float dt)
{
	if (!gameData->assets.SoundStillPlaying(SPLASH_SOUND))
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
