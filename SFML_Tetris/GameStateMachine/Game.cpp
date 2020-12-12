#include "Game.h"
#include "SplashState.h"

Game::Game()
{
	LoadAssets();
	BasicSetup();

	gameData->machine.AddState(std::make_unique<SplashState>(gameData));
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
			if (event.type == sf::Event::KeyPressed)
			{
				gameData->machine.GetActiveState()->HandleInput(event);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				gameData->machine.GetActiveState()->HandleInput(event);
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

//// **** Private Functions ****

void Game::BasicSetup()
{
	gameData->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE,
		sf::Style::Close | sf::Style::Titlebar);
	gameData->window.setVerticalSyncEnabled(true);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	gameData->window.setPosition({ (int)desktop.width / 2 - (int)gameData->window.getSize().x / 2, 0 });
	icon = gameData->assets.GetImage(WINDOW_ICON);
	sf::Vector2u iconSize = icon.getSize();
	gameData->window.setIcon(iconSize.x, iconSize.y, icon.getPixelsPtr());

	FileHandler::CreateAppDataDirectory();
}

void Game::LoadAssets()
{
	gameData->assets.LoadFont(UNISPACE_FONT, UNISPACE_FONT_PATH);
	gameData->assets.LoadSound(SELECTION_SOUND, SELECTION_SOUND_PATH);
	gameData->assets.LoadSound(FALL_SOUND, FALL_SOUND_PATH);
	gameData->assets.LoadSound(GAMEOVER_SOUND, GAMEOVER_SOUND_PATH);
	gameData->assets.LoadSound(LINE_SOUND, LINE_SOUND_PATH);
	gameData->assets.LoadSound(TETRIS_SOUND, TETRIS_SOUND_PATH);
	gameData->assets.LoadSound(SPLASH_SOUND, SPLASH_SOUND_PATH);
	gameData->assets.LoadTexture(SPLASH_SCREEN, SPLASH_SCREEN_PATH);
	gameData->assets.LoadImage(WINDOW_ICON, WINDOW_ICON_PATH);
}
