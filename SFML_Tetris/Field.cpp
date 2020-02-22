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

void Field::Draw(sf::RenderWindow& wnd)
{
	for (auto cell : cells)
	{
		wnd.draw(cell.shape);
	}
}
