#include "Cell.h"

Cell::Cell(const float xPos, const float yPos, const sf::Color background)
{
	shape.setSize({ (float)Dimensions, (float)Dimensions });
	shape.setPosition({ xPos, yPos });
	shape.setFillColor(background);
	shape.setOutlineThickness(outLineThick);
	shape.setOutlineColor(outlineColor);
}

Cell::Cell(const Cell& src)
{
	*this = src;
}

Cell& Cell::operator=(const Cell& src)
{
	occupied = src.occupied;
	shape = sf::RectangleShape(src.shape.getSize());
	shape.setPosition(src.shape.getPosition());
	shape.setFillColor(src.shape.getFillColor());
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(outLineThick);

	return *this;
}

void Cell::SetFillColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Cell::SetOutlineColor(sf::Color color)
{
	shape.setOutlineColor(color);
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

void Cell::MoveDown()
{
	auto pos = shape.getPosition();
	shape.setPosition(pos.x, pos.y + Cell::Dimensions);
}
