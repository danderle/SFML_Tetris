#pragma once
#include "SFML/Graphics.hpp"

class Cell
{
public:
	Cell() = delete;
	Cell(const float xPos, const float yPos, const sf::Color background);
	Cell(const Cell& src);
	Cell& operator=(const Cell& src);

	void SetColor(sf::Color color);
	const sf::Color GetColor() const;
	void Occupied();
	void NotOccupied();
	const bool IsOccupied() const;
	const sf::RectangleShape& GetShape() const;
	void MoveDown();

public:
	static constexpr int Dimensions = 35;

private:
	sf::RectangleShape shape;
	bool occupied = false;
	
	const sf::Color outlineColor = sf::Color::Black;
	
	static constexpr int outLineThick = -1;
};

