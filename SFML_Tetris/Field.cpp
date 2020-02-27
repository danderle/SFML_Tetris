#include "Field.h"

Field::Field(const sf::Vector2f _position)
	:position(_position)
{
	int vectorSize = width * height;
	for (int cell = 0; cell < vectorSize; cell++)
	{
		int row = cell / 10;
		int col = cell % 10;
		auto cellPosX = position.x + (col * Cell::Dimensions);
		auto cellPosY = position.y + (row * Cell::Dimensions);
		Cell newCell(cellPosX, cellPosY);
		cells.push_back(newCell);
	}
}

void Field::ShowOnField(Tetrimino& tetrimino)
{
	int row = tetrimino.GetRow();
	int column = tetrimino.GetColumn();
	unsigned int index = Field::width * row + column;
	sf::Color color = tetrimino.GetColor();
	ClearField();

	auto tetri = tetrimino.GetPosition();
	for (auto tetriRow : tetri)
	{
		for (auto tetriCol : tetriRow)
		{
			if (tetriCol)
			{
				if (index < cells.size())
				{
					cells[index].SetColor(color);
				}
			}
			index++;
		}
		row++;
		index = Field::width * row + column;
	}
}

const bool Field::CanMoveLeft(const Tetrimino& tetrimino) const
{
	bool canMove = true;
	int row = tetrimino.GetRow();
	int column = tetrimino.GetColumn() - 1;
	if (column < 0)
	{
		canMove = false;
		return canMove;
	}
	canMove = NextMoveFree(row, column, tetrimino);
	return canMove;
}

const bool Field::CanMoveRight(const Tetrimino& tetrimino) const
{
	bool canMove = true;
	int row = tetrimino.GetRow();
	int column = tetrimino.GetColumn() + 1;
	int tetriWidth = tetrimino.GetWidth()-1;
	if (!(column + tetriWidth < width))
	{
		canMove = false;
		return canMove;
	}
	canMove = NextMoveFree(row, column, tetrimino);
	return canMove;
}

const bool Field::CanMoveDown(const Tetrimino& tetrimino) const
{
	bool canMove = true;
	int row = tetrimino.GetRow() + 1;
	int column = tetrimino.GetColumn();
	int tetriheight = tetrimino.GetHeight()-1;
	if (!(row + tetriheight < height))
	{
		canMove = false;
		return canMove;
	}
	canMove = NextMoveFree(row, column, tetrimino);
	return canMove;
}

void Field::Draw(sf::RenderWindow& wnd)
{
	for (auto cell : cells)
	{
		wnd.draw(cell.GetShape());
	}
}

void Field::PlaceLastPositionOnField(const sf::Color tetriminoColor)
{
	for (int cell : lastPosition)
	{
		cells[cell].SetColor(tetriminoColor);
		cells[cell].Occupied();
	}
}

void Field::ClearFieldAndSaveLastPosition()
{
	std::vector<int> tetriLastPos;
	for (unsigned int cell = 0; cell < cells.size(); cell++)
	{
		if (!cells[cell].IsOccupied())
		{
			if (cells[cell].GetColor() != sf::Color::Red)
			{
				tetriLastPos.push_back(cell);
			}
			cells[cell].SetColor(sf::Color::Red);
		}
	}
	lastPosition = tetriLastPos;
}


//// **** Private Functions ****

void Field::ClearField()
{
	for (unsigned int cell = 0; cell < cells.size(); cell++)
	{
		if (!cells[cell].IsOccupied())
		{
			cells[cell].SetColor(sf::Color::Red);
		}
	}
}

const bool Field::NextMoveFree(int row, int column, const Tetrimino& tetrimino) const
{
	bool canMove = true;
	unsigned int index = Field::width * row + column;
	auto tetri = tetrimino.GetPosition();
	for (auto tetriRow : tetri)
	{
		for (auto tetriCol : tetriRow)
		{
			if (tetriCol)
			{
				if (cells[index].IsOccupied())
				{
					canMove = false;
					break;
				}
			}
			index++;
		}
		row++;
		index = Field::width * row + column;
	}
	return canMove;
}
