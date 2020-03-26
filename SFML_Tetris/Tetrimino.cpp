#include "Tetrimino.h"

Tetrimino::Tetrimino(std::vector<std::vector<bool>> _type, sf::Color _color)
	:
	type(_type),
	color(_color)
{
	isI = type.size() == 1;
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
}

void Tetrimino::RotateLeft()
{
	std::vector<std::vector<bool>> typeRotated;
	for (int col = type[0].size()-1; col >= 0; col--)
	{
		std::vector<bool> newRow;
		for (unsigned int row = 0; row < type.size(); row++)
		{
			newRow.push_back(type[row][col]);
		}
		typeRotated.push_back(newRow);
	}
	type = typeRotated;
	if (IsI())
	{
		AdjustIMove();
	}
}

void Tetrimino::RotateRight()
{
	std::vector<std::vector<bool>> typeRotated;
	for (unsigned int col = 0; col < type[0].size(); col++)
	{
		std::vector<bool> newRow;
		for (int row = type.size()-1; row >= 0; row--)
		{
			newRow.push_back(type[row][col]);
		}
		typeRotated.push_back(newRow);
	}
	type = typeRotated;
	if (IsI())
	{
		AdjustIMove();
	}
}

void Tetrimino::AdjustIMove()
{
	horizontal = horizontal ? false : true;
	if (horizontal)
	{
		MoveLeft();
	}
	else
	{
		MoveRight();
	}
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
	return type[0].size()-1;
}

int Tetrimino::GetHeight() const
{
	return type.size()-1;
}

const bool Tetrimino::IsI() const
{
	return isI;
}

std::vector<std::vector<bool>> Tetrimino::GetPosition() const
{
	return type;
}

sf::Color Tetrimino::GetColor() const
{
	return color;
}
