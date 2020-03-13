#include "Button.h"
#include <DEFINITIONS.h>

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

void Button::MouseHoverEffect(const bool mouseIsHovering)
{
	if (mouseIsHovering)
	{
		shape.setFillColor(textColor);
		centerText.setFillColor(BLACK);
		shape.setOutlineColor(BLACK);
	}
	else
	{
		shape.setFillColor(BLACK);
		centerText.setFillColor(textColor);
		shape.setOutlineColor(textColor);
	}
}
