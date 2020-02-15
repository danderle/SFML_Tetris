#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "InputManager.h"
#include "AssetManager.h"

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
	Game() = delete;
	Game(int width, int height, std::string title);

private:
	void Run();

private:
	sf::Clock clock;
	std::shared_ptr<GameData> gameData = std::make_shared<GameData>();
};

