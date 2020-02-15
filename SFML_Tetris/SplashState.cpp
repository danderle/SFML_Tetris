#include "SplashState.h"

SplashState::SplashState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData)
{
	test = "Constructed";
}

void SplashState::Init()
{
}

void SplashState::HandleInput()
{
}

void SplashState::Update(float dt)
{
}

void SplashState::Draw()
{
	gameData->window.clear();
	gameData->window.display();
}
