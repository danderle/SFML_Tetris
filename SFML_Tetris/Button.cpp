#include "Button.h"

Button::Button(float width, float height, const sf::Color backColor)
	: Button({ width, height }, { 0, 0 }, backColor)
{
}

Button::Button(const float width, const float height, const float xPos, const float yPos, const sf::Color backColor)
	: Button({width, height}, {xPos, yPos}, backColor)
{
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Color backColor)
	:
	TextBox(size, position, backColor)
{
	SetOutline(backColor, -2);
}

void Button::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
	if (isTextSet)
	{
		wnd.draw(centerText);
	}
}

void Button::MouseHover(const bool mouseIsHovering)
{
	if (mouseIsHovering)
	{
		shape.setFillColor(sf::Color::Transparent);
		centerText.setFillColor(color);
	}
	else
	{
		shape.setFillColor(color);
		centerText.setFillColor(sf::Color::Black);
	}
}
