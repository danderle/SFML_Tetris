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
	shape(size),
	color(backColor)
{
	shape.setPosition(position);
	SetBackColor(color);
}

Button::Button(const std::string content, const sf::Color backColor)
{
	SetContent(content);
}

void Button::SetFont(const sf::Font& font)
{
	text.setFont(font);
	isTextSet = true;
}

void Button::SetContent(const std::string& content)
{
	text.setString(content);
}

void Button::SetPosition(const sf::Vector2f position)
{
	shape.setPosition(position);
	text.setPosition(position);
	CenterText();
}

void Button::SetCenterAt(sf::Vector2f position)
{
	position.x -= (shape.getSize().x / 2);
	position.y -= (shape.getSize().y / 2);
	SetPosition(position);
}

void Button::SetBackColor(const sf::Color backColor)
{
	color = backColor;
	shape.setFillColor(color);
	shape.setOutlineColor(color);
	shape.setOutlineThickness(-2);
}

void Button::CenterText()
{
	auto textPosition = text.getPosition();
	float x = text.getLocalBounds().left;
	float y = text.getLocalBounds().top;
	x += (text.getLocalBounds().width - shape.getSize().x)/2;
	y += (text.getLocalBounds().height - shape.getSize().y)/2;
	text.setOrigin({ x,y });
}

void Button::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
	if (isTextSet)
	{
		wnd.draw(text);
	}
}

void Button::MouseHover(const sf::Vector2i msePosition)
{
	if (shape.getGlobalBounds().contains({ (float)msePosition.x, (float)msePosition.y }))
	{
		shape.setFillColor(sf::Color::Transparent);
	}
	else
	{
		shape.setFillColor(color);
	}
}
