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

	void Enable();
	void Disable();
	const bool IsEnabled() const;
	virtual void Draw(sf::RenderWindow& wnd) override;
	void MouseHoverEffect(const bool mouseIsHovering);

private:
	void SetStandardDisplay();
	void SetHoverDisplay();
	void SetDisabledDisplay();

private:
	bool enabled = true;
};

