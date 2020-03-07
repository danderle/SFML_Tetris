#pragma once
#include "SFML/Graphics.hpp"
#include "TextBox.h"

class Button : public TextBox
{
public:
	Button() = delete;
	Button(float width, float height, const sf::Color backColor = sf::Color::Green);
	Button(float width, float height, float xPos, float yPos, const sf::Color backColor = sf::Color::Green);
	Button(sf::Vector2f size, sf::Vector2f position, const sf::Color backColor = sf::Color::Green);

	virtual void Draw(sf::RenderWindow& wnd) override;
	void MouseHover(const bool mouseIsHovering);
};

