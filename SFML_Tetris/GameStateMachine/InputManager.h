#pragma once
#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	bool IsRectClicked(sf::Rect<float> rect, sf::Mouse::Button buttonPressed, sf::RenderWindow& window);
	bool IsHovering(sf::Rect<float> rect, sf::RenderWindow& window);
	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
};

