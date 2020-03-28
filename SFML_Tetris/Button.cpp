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
	SetOutlineColor(backColor, -2);
}

void Button::Enable()
{
	enabled = true;
	SetStandardDisplay();
}

void Button::Disable()
{
	enabled = false;
	SetDisabledDisplay();
}

const bool Button::IsEnabled() const
{
	return enabled;
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
	if (!enabled)
	{
		SetDisabledDisplay();
	}
	else if(mouseIsHovering)
	{
		SetHoverDisplay();
	}
	else
	{
		SetStandardDisplay();
	}
}

void Button::SetStandardDisplay()
{
	shape.setFillColor(backColor);
	centerText.setFillColor(BLACK);
	shape.setOutlineColor(BLACK);
}

void Button::SetHoverDisplay()
{
	shape.setFillColor(BLACK);
	centerText.setFillColor(backColor);
	shape.setOutlineColor(outlineColor);
}

void Button::SetDisabledDisplay()
{
	shape.setFillColor(LIGHTGRAY);
	centerText.setFillColor(BLACK);
	shape.setOutlineColor(BLACK);
}
