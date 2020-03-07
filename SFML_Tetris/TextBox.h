#pragma once
#include "SFML/Graphics.hpp"

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
	void SetPosition(const sf::Vector2f position);
	void SetCenterAt(sf::Vector2f position);
	void SetBackColor(const sf::Color backColor);
	void SetOutline(const sf::Color color, const float thickness);
	void CenterTopText();
	void CenterText();
	const sf::Vector2f GetPosition() const;
	virtual void Draw(sf::RenderWindow& wnd);

public:
	static constexpr int Margin = 6;
	static constexpr int Padding = 5;

protected:
	sf::RectangleShape shape;
	sf::Text topText;
	sf::Text centerText;
	sf::Color color;
	bool isTextSet = false;
	float outlineThickness = 0.f;
};

