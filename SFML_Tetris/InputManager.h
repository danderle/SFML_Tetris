#pragma once
#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	bool IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window);
	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
};

