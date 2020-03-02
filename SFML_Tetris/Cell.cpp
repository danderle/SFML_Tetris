#include "Cell.h"

Cell::Cell(const float xPos, const float yPos)
{
	shape.setSize({ (float)Dimensions, (float)Dimensions });
	shape.setPosition({ xPos, yPos });
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineThickness(outLineThick);
	shape.setOutlineColor(outlineColor);
}

Cell::Cell(const Cell& src)
{
	*this = src;
}

Cell& Cell::operator=(const Cell& src)
{
	shape = sf::RectangleShape(src.shape);
	occupied = src.occupied;

	return *this;
}

void Cell::SetColor(sf::Color color)
{
	shape.setFillColor(color);
}

const sf::Color Cell::GetColor() const
{
	return shape.getFillColor();
}

void Cell::Occupied()
{
	occupied = true;
}

void Cell::NotOccupied()
{
	occupied = false;
}

const bool Cell::IsOccupied() const
{
	return occupied;
}

const sf::RectangleShape& Cell::GetShape() const
{
	return shape;
}
