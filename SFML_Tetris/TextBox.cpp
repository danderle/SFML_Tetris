#include "TextBox.h"

TextBox::TextBox(float width, float height, const sf::Color backColor)
	:
	TextBox(width, height, 0, 0, backColor)
{
}

TextBox::TextBox(float width, float height, float xPos, float yPos, const sf::Color backColor)
	:
	TextBox({width, height}, {xPos, yPos}, backColor)
{
}

TextBox::TextBox(sf::Vector2f size, sf::Vector2f position, const sf::Color backColor)
	:
	shape(size),
	color(backColor)
{
	shape.setPosition(position);
	SetBackColor(color);
}

const sf::FloatRect TextBox::GetRect() const
{
	return shape.getGlobalBounds();
}

void TextBox::SetFont(const sf::Font& font)
{
	text.setFont(font);
}

void TextBox::SetContent(const std::string& content)
{
	text.setString(content);
}

void TextBox::SetPosition(const sf::Vector2f position)
{
	shape.setPosition(position);
	text.setPosition(position);
	CenterText();
}

void TextBox::SetCenterAt(sf::Vector2f position)
{
	position.x -= (shape.getSize().x / 2);
	position.y -= (shape.getSize().y / 2);
	SetPosition(position);
}

void TextBox::SetBackColor(const sf::Color backColor)
{
	color = backColor;
	shape.setFillColor(color);
}

void TextBox::SetOutline(const sf::Color color, const float thickness)
{
	shape.setOutlineColor(color);
	shape.setOutlineThickness(thickness);
}

void TextBox::CenterText()
{
	auto textPosition = text.getPosition();
	float x = text.getLocalBounds().left;
	float y = text.getLocalBounds().top;
	x += (text.getLocalBounds().width - shape.getSize().x) / 2;
	y += (text.getLocalBounds().height - shape.getSize().y) / 2;
	text.setOrigin({ x,y });
}

void TextBox::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
	wnd.draw(text);
}

