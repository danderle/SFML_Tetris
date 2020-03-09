#include "Field.h"

Field::Field(const sf::Vector2f _position)
	:
	position(_position),
	frame({Width, Height})
{
	frame.setPosition(position);
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(LIGHTGRAY);
	frame.setOutlineThickness(Field::FrameThickness);
	int vectorSize = columns * rows;
	for (int cell = 0; cell < vectorSize; cell++)
	{
		int row = cell / 10;
		int col = cell % 10;
		auto cellPosX = position.x + (col * Cell::Dimensions);
		auto cellPosY = position.y + (row * Cell::Dimensions);
		Cell newCell(cellPosX, cellPosY, backgroundColor);
		cells.push_back(newCell);
	}
	std::copy(cells.begin(), cells.begin() + Field::columns, std::back_inserter(firstRow));
}

void Field::ShowOnField(Tetrimino& tetrimino)
{
	int row = tetrimino.GetRow();
	int column = tetrimino.GetColumn();
	unsigned int index = Field::columns * row + column;
	sf::Color color = tetrimino.GetColor();
	ClearField();

	auto tetri = tetrimino.GetPosition();
	for (auto tetriRow : tetri)
	{
		for (auto tetriCol : tetriRow)
		{
			if (tetriCol)
			{
				if (index < cells.size() && index >= 0)
				{
					cells[index].SetColor(color);
				}
			}
			index++;
		}
		row++;
		index = Field::columns * row + column;
	}
}

const bool Field::CanMoveLeft(const Tetrimino& tetrimino) const
{
	bool canMove = false;
	int row = tetrimino.GetRow();
	if (row >= 0)
	{
		int column = tetrimino.GetColumn() - 1;
		if (column < 0)
		{
			canMove = false;
			return canMove;
		}
		canMove = NextMoveFree(row, column, tetrimino);
	}
	return canMove;
}

const bool Field::CanMoveRight(const Tetrimino& tetrimino) const
{
	bool canMove = false;
	int row = tetrimino.GetRow();
	if (row >= 0)
	{
		int column = tetrimino.GetColumn() + 1;
		int tetriWidth = tetrimino.GetWidth();
		if (!(column + tetriWidth < columns))
		{
			canMove = false;
			return canMove;
		}
		canMove = NextMoveFree(row, column, tetrimino);
	}
	return canMove;
}

const bool Field::CanMoveDown(const Tetrimino& tetrimino) const
{
	bool canMove = true;
	int row = tetrimino.GetRow() + 1;
	int column = tetrimino.GetColumn();
	int tetriheight = tetrimino.GetHeight();
	if (!(row + tetriheight < rows))
	{
		canMove = false;
		return canMove;
	}
	canMove = NextMoveFree(row, column, tetrimino);
	return canMove;
}

const bool Field::CanRotate(Tetrimino& tetrimino) const
{
	bool canMove = false;
	int row = tetrimino.GetRow();
	if (row >= 0)
	{
		int column = tetrimino.GetColumn();
		int tetriheight = tetrimino.GetHeight();
		int tetriWidth = tetrimino.GetWidth();
		if (!(column + tetriWidth < columns))
		{
			while (column + tetriWidth >= columns)
			{
				tetrimino.MoveLeft();
				column--;
			}
		}
		if (!(row + tetriheight < rows))
		{
			return canMove;
		}
		canMove = NextMoveFree(row, column, tetrimino);
	}
	return canMove;
}

void Field::ClearFieldAndSaveLastPosition()
{
	std::vector<int> tetriLastPos;
	for (unsigned int cell = 0; cell < cells.size(); cell++)
	{
		if (!cells[cell].IsOccupied())
		{
			if (cells[cell].GetColor() != backgroundColor)
			{
				tetriLastPos.push_back(cell);
			}
			cells[cell].SetColor(backgroundColor);
		}
	}
	lastPosition = tetriLastPos;
}

void Field::PlaceLastPositionOnField(const sf::Color tetriminoColor)
{
	for (int cell : lastPosition)
	{
		cells[cell].SetColor(tetriminoColor);
		cells[cell].Occupied();
	}
}

void Field::ClearFullRows(unsigned int& currentScore, unsigned int& linesCleared, unsigned int& level)
{
	int occupiedCounter = 0;
	bool rowCleared = false;
	std::vector<int> clearedRows;
	for (int row = 0; row < rows; row++)
	{
		if (RowIsFull(row))
		{
			ClearRow(row);
			clearedRows.push_back(row);
			rowCleared = true;
		}
	}
	if (rowCleared)
	{
		unsigned int numOfClearedRows = clearedRows.size();
		linesCleared += numOfClearedRows;
		level = linesCleared / 10;
		level = level == 0 ? 1 : level;
		switch (numOfClearedRows)
		{
		case 1:
			currentScore += 40 * level;
			break;
		case 2:
			currentScore += 100 * level;
			break;
		case 3:
			currentScore += 300 * level;
			break;
		case 4:
			currentScore += 1200 * level;
			break;
		default:
			currentScore += 0;
		}
		std::reverse(clearedRows.begin(), clearedRows.end());
		int rowsMoved = 0;
		for (auto row : clearedRows)
		{
			row += rowsMoved;
			MoveAllRowsDown(row);
			rowsMoved++;
		}
	}
}

void Field::Draw(sf::RenderWindow& wnd)
{
	for (auto& cell : cells)
	{
		wnd.draw(cell.GetShape());
	}
	wnd.draw(frame);
}

//// **** Private Functions ****

void Field::ClearField()
{
	for (unsigned int cell = 0; cell < cells.size(); cell++)
	{
		if (!cells[cell].IsOccupied())
		{
			cells[cell].SetColor(backgroundColor);
		}
	}
}

const bool Field::NextMoveFree(int row, int column, const Tetrimino& tetrimino) const
{
	bool canMove = true;
	unsigned int index = Field::columns * row + column;
	auto tetri = tetrimino.GetPosition();
	for (auto tetriRow : tetri)
	{
		for (auto tetriCol : tetriRow)
		{
			if (tetriCol)
			{
				if (index >= 0 && cells[index].IsOccupied())
				{
					canMove = false;
					break;
				}
			}
			index++;
		}
		row++;
		index = Field::columns * row + column;
	}
	return canMove;
}

const bool Field::RowIsFull(const int row) const
{
	int occupiedCounter = 0;
	int column = 0;
	int index = Field::columns * row + column; 
	for (; column < Field::columns; column++, index++)
	{
		if (cells[index].IsOccupied())
		{
			occupiedCounter++;
		}
	}
	return occupiedCounter == Field::columns;
}

void Field::ClearRow(const int row)
{
	int column = 0;
	int index = Field::columns * row + column; 
	for (int column = 0; column < Field::columns; column++, index++)
	{
		cells[index].NotOccupied();
	}
}

void Field::MoveAllRowsDown(const int row)
{
	int column = 0;
	int upTo = Field::columns * row + column;
	std::transform(cells.begin(), cells.begin() + upTo, cells.begin(), 
		[](Cell cell) 
		{
			cell.MoveDown(); 
			return cell; 
		});
	std::copy_backward(cells.begin(), cells.begin() + upTo, cells.begin() + Field::columns + upTo);
	std::copy(firstRow.begin(), firstRow.end(), cells.begin());
}

