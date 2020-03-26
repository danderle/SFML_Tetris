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
	int vectorSize = Field::Columns * Field::Rows;
	for (int cell = 0; cell < vectorSize; cell++)
	{
		int row = cell / 10;
		int col = cell % 10;
		auto cellPosX = position.x + (col * Cell::Dimensions);
		auto cellPosY = position.y + (row * Cell::Dimensions);
		Cell newCell(cellPosX, cellPosY, backgroundColor);
		cells.push_back(newCell);
	}
	std::copy(cells.begin(), cells.begin() + Field::Columns, std::back_inserter(firstRow));
}

void Field::ShowOnField(Tetrimino& tetrimino)
{
	int row = tetrimino.GetRow();
	int column = tetrimino.GetColumn();
	unsigned int index = Field::Columns * row + column;
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
					cells[index].SetFillColor(color);
				}
			}
			index++;
		}
		row++;
		index = Field::Columns * row + column;
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
		if (!(column + tetriWidth < Field::Columns))
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
	if (!(row + tetriheight < Field::Rows))
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
		if (!(column + tetriWidth < Field::Columns))
		{
			while (column + tetriWidth >= Field::Columns)
			{
				tetrimino.MoveLeft();
				column--;
			}
		}
		if (!(row + tetriheight < Field::Rows))
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
			cells[cell].SetFillColor(backgroundColor);
		}
	}
	lastPosition = tetriLastPos;
}

void Field::PlaceLastPositionOnField(const sf::Color tetriminoColor)
{
	for (int cell : lastPosition)
	{
		cells[cell].SetFillColor(tetriminoColor);
		cells[cell].Occupied();
	}
}

void Field::UpdatePoints(unsigned int& currentScore, unsigned int& linesCleared, unsigned int& level)
{
	unsigned int numOfClearedRows = fullRows.size();
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
	
}

const bool Field::FindFullRows()
{
	for (int row = 0; row < Field::Rows; row++)
	{
		if (RowIsFull(row))
		{
			fullRows.push_back(row);
			foundFullRow = true;
		}
	}
	return foundFullRow;
}

const bool Field::IsFlashing() const
{
	return foundFullRow;
}


void Field::FlashFullRows(const float dt)
{
	int column = 0;
	innerFlash.r += colorChanger;
	innerFlash.g += colorChanger;
	innerFlash.b += colorChanger;
	outerFlash.r -= colorChanger;
	outerFlash.g -= colorChanger;
	outerFlash.b -= colorChanger;
	if (innerFlash.r < 0)
	{
		innerFlash = BLACK;
		outerFlash = WHITE;
		colorChanger *= -1;
	}
	else if (innerFlash.r > 255)
	{
		innerFlash = WHITE;
		outerFlash = BLACK;
		colorChanger *= -1;
	}
	for (auto row : fullRows)
	{
		for (int column = 0; column < Field::Columns; column++)
		{
			int index = Field::Columns * row + column;
			cells[index].SetFillColor(innerFlash);
			cells[index].SetOutlineColor(outerFlash);
		}
	}
	totalFlashTime += dt;
	if (totalFlashTime > flashTime)
	{
		foundFullRow = false;
		totalFlashTime = 0;
		MoveAllRowsDown();
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
			cells[cell].SetFillColor(backgroundColor);
		}
	}
}

const bool Field::NextMoveFree(int row, int column, const Tetrimino& tetrimino) const
{
	bool canMove = true;
	unsigned int index = Field::Columns * row + column;
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
		index = Field::Columns * row + column;
	}
	return canMove;
}

const bool Field::RowIsFull(const int row) const
{
	int occupiedCounter = 0;
	int column = 0;
	int index = Field::Columns * row + column; 
	for (; column < Field::Columns; column++, index++)
	{
		if (cells[index].IsOccupied())
		{
			occupiedCounter++;
		}
	}
	return occupiedCounter == Field::Columns;
}

void Field::SetRowUnoccupied(const int row)
{
	int column = 0;
	int index = Field::Columns * row + column; 
	for (int column = 0; column < Field::Columns; column++, index++)
	{
		cells[index].NotOccupied();
	}
}

void Field::MoveAllRowsDown()
{
	std::reverse(fullRows.begin(), fullRows.end());
	int rowsMoved = 0;
	for (auto row : fullRows)
	{
		row += rowsMoved;
		MoveRowDown(row);
		rowsMoved++;
	}
	fullRows.clear();
}

void Field::MoveRowDown(const int row)
{
	int column = 0;
	int upTo = Field::Columns * row + column;
	std::transform(cells.begin(), cells.begin() + upTo, cells.begin(), 
		[](Cell cell) 
		{
			cell.MoveDown(); 
			return cell; 
		});
	std::copy_backward(cells.begin(), cells.begin() + upTo, cells.begin() + Field::Columns + upTo);
	std::copy(firstRow.begin(), firstRow.end(), cells.begin());
}


