#include "Tetrimino.h"

Tetrimino::Tetrimino(std::vector<std::vector<bool>> _type, sf::Color _color)
	:
	type(_type),
	color(_color),
	rowPos(0),
	colPos(5)
{
	
}

void Tetrimino::MoveDown()
{
	rowPos += 1;
}

void Tetrimino::MoveLeft()
{
	colPos -= 1;
	colPos = colPos >= 0 ? colPos : 0;
}

void Tetrimino::MoveRight()
{
	colPos += 1;
	colPos = (colPos + type.size()) < 10 ? colPos : 10 - type.size();
}

int Tetrimino::GetRow() const
{
	return rowPos;
}

int Tetrimino::GetColumn() const
{
	return colPos;
}

int Tetrimino::GetWidth() const
{
	return type[0].size();
}

int Tetrimino::GetHeight() const
{
	return type.size();
}

std::vector<std::vector<bool>> Tetrimino::GetPosition() const
{
	return type;
}

sf::Color Tetrimino::GetColor() const
{
	return color;
}
