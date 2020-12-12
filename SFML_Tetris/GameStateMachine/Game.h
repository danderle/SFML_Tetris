#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "FileHandler.h"
#include "StateMachine.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "DEFINITIONS.h"

struct GameData
{
	StateMachine machine;
	AssetManager assets;
	InputManager input;
	sf::RenderWindow window;
};

class Game
{
public:
	Game();
	void Run();

private:
	void BasicSetup();
	void LoadAssets();

private:
	sf::Clock clock;
	std::shared_ptr<GameData> gameData = std::make_shared<GameData>();
	sf::Image icon;
};

