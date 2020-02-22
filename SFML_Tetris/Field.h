#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Field
{
private:
	class Cell
	{
	public:
		Cell(const float xPos, const float yPos)
		{
			shape.setSize({ (float)Dimensions, (float)Dimensions });
			shape.setPosition({ xPos, yPos });
			color = sf::Color::Red;
			shape.setFillColor(color);
			shape.setOutlineThickness(outLineThick);
			shape.setOutlineColor(outlineColor);
		}
		sf::RectangleShape shape;
		sf::Color color = sf::Color::Red;
		static constexpr int Dimensions = 35;
	private:
		static constexpr int outLineThick = -1;
		const sf::Color outlineColor = sf::Color::Black;
	};
public:
	Field() = delete;
	Field(const sf::Vector2f _position);

	void Draw(sf::RenderWindow& wnd);
private:
	sf::Vector2f position;
	std::vector<Cell> cells;
	static constexpr int width = 10;
	static constexpr int height = 24;
};

