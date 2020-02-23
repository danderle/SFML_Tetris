#include "Tetrimino.h"

Tetrimino::Tetrimino(std::vector<std::vector<bool>> type, sf::Color _color)
	:
	tetri(type),
	color(_color),
	rowPos(0),
	colPos(5)
{
}

void Tetrimino::MoveDown()
{
	rowPos += 1;
}

int Tetrimino::GetRow() const
{
	return rowPos;
}

int Tetrimino::GetColumn() const
{
	return colPos;
}

std::vector<std::vector<bool>> Tetrimino::GetPosition() const
{
	return tetri;
}

sf::Color Tetrimino::GetColor() const
{
	return color;
}

void Tetrimino::PlacedOnField()
{
	isPlacedOnField = true;
}

const bool Tetrimino::IsPlacedOnField() const
{
	return isPlacedOnField;
}
