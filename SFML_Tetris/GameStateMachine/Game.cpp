#include "Game.h"
#include "../States/SplashState.h"

Game::Game(int width, int height, std::string title)
{
	gameData->window.create(sf::VideoMode(width, height), title, 
		sf::Style::Close | sf::Style::Titlebar);
	gameData->machine.AddState(std::make_unique<SplashState>(gameData));
	Run();
}

void Game::Run()
{
	float dt;
	float frameTime;
	float currentTime = clock.getElapsedTime().asSeconds();
	float fps;
	while (gameData->window.isOpen())
	{
		sf::Event event;
		while (gameData->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				gameData->window.close();
			}
		}
		gameData->machine.ProcessStateChanges();
		frameTime = clock.restart().asSeconds();
		fps = 1.f / frameTime;
		dt = frameTime / fps;
		while (fps > 0)
		{
			gameData->machine.GetActiveState()->HandleInput();
			gameData->machine.GetActiveState()->Update(dt);
			gameData->machine.GetActiveState()->Draw();
			fps--;
		}
	}

}
