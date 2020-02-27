#include "Tetrimino.h"

Tetrimino::Tetrimino(std::vector<std::vector<bool>> type, sf::Color _color)
	:
	tetri(type),
	color(_color),
	rowPos(0),
	colPos(5),
	rng(rnd()),
	colorIndex(0, 5),
	typeIndex(0,6)
{
	int index = colorIndex(rng);
	color = colors[index];
	index = typeIndex(rng);
	tetri = types[index];
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
	colPos = (colPos + tetri.size()) < 10 ? colPos : 10 - tetri.size();
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
	return tetri[0].size();
}

int Tetrimino::GetHeight() const
{
	return tetri.size();
}

std::vector<std::vector<bool>> Tetrimino::GetPosition() const
{
	return tetri;
}

sf::Color Tetrimino::GetColor() const
{
	return color;
}
