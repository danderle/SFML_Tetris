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
	bool KeyHit(sf::Keyboard::Key key) const;
	bool KeyReleased(sf::Event event, sf::Keyboard::Key key) const;
};

