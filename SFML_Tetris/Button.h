#pragma once
#include "SFML/Graphics.hpp"

class Button
{
public:
	Button() = delete;
	Button(float width, float height, const sf::Color backColor = sf::Color::Green);
	Button(float width, float height, float xPos, float yPos, const sf::Color backColor = sf::Color::Green);
	Button(sf::Vector2f size, sf::Vector2f position, const sf::Color backColor = sf::Color::Green);
	Button(std::string content, const sf::Color backColor = sf::Color::Green);

	void SetFont(const sf::Font& font);
	void SetContent(const std::string& content);
	void SetPosition(const sf::Vector2f position);
	void SetCenterAt(sf::Vector2f position);
	void SetBackColor(const sf::Color backColor);
	void CenterText();
	void Draw(sf::RenderWindow& wnd);
	void MouseHover(const sf::Vector2i msePosition);

private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Color color;
	bool isTextSet = false;
};

