#pragma once
#include "SFML/Graphics.hpp"
#include "DEFINITIONS.h"

enum class Alignment
{
	TOP,
	CENTER,
};

class TextBox
{
public:
	TextBox() = delete;
	TextBox(float width, float height, const sf::Color backColor = sf::Color::Green);
	TextBox(float width, float height, float xPos, float yPos, const sf::Color backColor = sf::Color::Green);
	TextBox(sf::Vector2f size, sf::Vector2f position, const sf::Color backColor = sf::Color::Green);

	const sf::FloatRect GetRect() const;
	virtual void SetFont(const sf::Font& font, const unsigned int charSize = 30);
	void SetContent(const std::string& content, const Alignment alignment);
	void SetPosition(const float xPosition, const float yPosition);
	void SetPosition(const sf::Vector2f position);
	void SetCenterAt(const float xPosition, const float yPosition);
	void SetCenterAt(sf::Vector2f position);
	void SetBackColor(const sf::Color backColor);
	void SetTextColor(sf::Color color);
	void SetOutlineColor(const sf::Color color, const float thickness);
	void CenterTopText();
	void CenterText();
	const sf::Vector2f GetPosition() const;
	void SetTemplate(const sf::Font& font, const std::string content);
	std::string GetContent(const Alignment alignment);
	virtual void Draw(sf::RenderWindow& wnd);

public:
	static constexpr int Margin = 6;
	static constexpr int Padding = 5;

protected:
	sf::RectangleShape shape;
	sf::Text topText;
	sf::Text centerText;
	sf::Color backColor;
	sf::Color outlineColor;
	sf::Color textColor;
	bool isTextSet = false;
	float outlineThickness = 0.f;
};

