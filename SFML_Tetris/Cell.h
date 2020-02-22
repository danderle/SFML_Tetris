#pragma once
#include "SFML/Graphics.hpp"

class Cell
{
public:
	Cell() = delete;
	Cell(const float xPos, const float yPos);
	
	void SetColor(sf::Color color);
	const sf::Color GetColor() const;
	void Occupied();
	void NotOccupied();
	const bool IsOccupied() const;
	const sf::RectangleShape& GetShape() const;
public:
	static constexpr int Dimensions = 35;

private:
	sf::RectangleShape shape;
	bool occupied = false;
	static constexpr int outLineThick = -1;
	const sf::Color outlineColor = sf::Color::Black;
};

