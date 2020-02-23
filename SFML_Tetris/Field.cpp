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
	auto tetriLastPos = ClearFieldAndSaveLastPosition(index);

	auto tetri = tetrimino.GetPosition();
	bool placeTetriInField = false;
	for (auto tetriRow : tetri)
	{
		for (auto tetriCol : tetriRow)
		{
			if (tetriCol)
			{
				if (index < cells.size() && !cells[index].IsOccupied() )
				{
					cells[index].SetColor(color);
				}
				else
				{
					placeTetriInField = true;
					break;
				}
			}
			index++;
		}
		row++;
		index = Field::width * row + column;
	}
	if (placeTetriInField)
	{
		PlaceOnField(tetriLastPos, color);
		tetrimino.PlacedOnField();
	}
}

void Field::Draw(sf::RenderWindow& wnd)
{
	for (auto cell : cells)
	{
		wnd.draw(cell.GetShape());
	}
}

void Field::PlaceOnField(const std::vector<int>& lastPosition, const sf::Color color)
{
	for (int cell : lastPosition)
	{
		cells[cell].SetColor(color);
		cells[cell].Occupied();
	}
}

const std::vector<int> Field::ClearFieldAndSaveLastPosition(int index)
{
	std::vector<int> tetriLastPos;
	for (int cell = 0; cell < index; cell++)
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
	return tetriLastPos;
}
