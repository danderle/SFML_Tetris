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

TextBox::TextBox(sf::Vector2f size, sf::Vector2f position, const sf::Color _backColor)
	:
	shape(size),
	backColor(_backColor)
{
	shape.setPosition(position);
	SetBackColor(backColor);
}

const sf::FloatRect TextBox::GetRect() const
{
	return shape.getGlobalBounds();
}

void TextBox::SetFont(const sf::Font& font, const unsigned int charSize)
{
	centerText.setFont(font);
	topText.setFont(font);
	centerText.setCharacterSize(charSize);
	topText.setCharacterSize(charSize);
	isTextSet = true;
}

void TextBox::SetContent(const std::string& content, const Alignment alignment)
{
	switch (alignment)
	{
	case Alignment::TOP:
		topText.setString(content);
		CenterTopText();
		break;
	case Alignment::CENTER:
		centerText.setString(content);
		CenterText();
		break;
	}
}

void TextBox::SetPosition(const float xPosition, const float yPosition)
{
	SetPosition({ xPosition, yPosition });
}

void TextBox::SetPosition(const sf::Vector2f position)
{
	shape.setPosition(position);
	topText.setPosition(position);
	centerText.setPosition(position);
}

void TextBox::SetCenterAt(const float xPosition, const float yPosition)
{
	SetCenterAt({ xPosition, yPosition });
}

void TextBox::SetCenterAt(sf::Vector2f position)
{
	position.x -= (shape.getSize().x / 2);
	position.y -= (shape.getSize().y / 2);
	SetPosition(position);
}

void TextBox::SetBackColor(const sf::Color _backColor)
{
	backColor = _backColor;
	shape.setFillColor(backColor);
}

void TextBox::SetTextColor(sf::Color color)
{
	textColor = color;
	topText.setFillColor(textColor);
	centerText.setFillColor(textColor);
}

void TextBox::SetOutlineColor(const sf::Color color, const float thickness)
{
	outlineColor = color;
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(thickness);
	outlineThickness = thickness;
}

void TextBox::CenterTopText()
{
	float x = topText.getLocalBounds().left;
	float y = topText.getLocalBounds().top;
	x += (topText.getLocalBounds().width - shape.getSize().x) / 2;
	y += outlineThickness - Padding;
	topText.setOrigin({ x,y });
}

void TextBox::CenterText()
{
	float x = centerText.getLocalBounds().left;
	float y = centerText.getLocalBounds().top;
	x += (centerText.getLocalBounds().width - shape.getSize().x) / 2;
	y += (centerText.getLocalBounds().height - shape.getSize().y) / 2;
	centerText.setOrigin({ x,y });
}

const sf::Vector2f TextBox::GetPosition() const
{
	return shape.getPosition();
}

void TextBox::SetTemplate(const sf::Font& font, const std::string content)
{
	SetFont(font, CHARACTER_SIZE);
	SetTextColor(BLACK);
	SetOutlineColor(GREEN, OUTLINE_THICKNESS);
	SetContent(content, Alignment::CENTER);
}

std::string TextBox::GetContent(const Alignment alignment)
{
	std::string text;
	switch (alignment)
	{
	case Alignment::CENTER:
		text = centerText.getString();
		break;
	case Alignment::TOP:
		text = topText.getString();
	}
	return text;
}

void TextBox::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
	wnd.draw(topText);
	wnd.draw(centerText);
}

