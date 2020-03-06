#pragma once
#include <vector>
#include <algorithm>
#include "DEFINITIONS.h"
#include "Cell.h"
#include "Tetrimino.h"

class Field
{
public:
	Field() = delete;
	Field(const sf::Vector2f _position);

	void ShowOnField(Tetrimino& tetrimino);
	const bool CanMoveLeft(const Tetrimino& tetrimino) const;
	const bool CanMoveRight(const Tetrimino& tetrimino) const;
	const bool CanMoveDown(const Tetrimino& tetrimino) const;
	const bool CanRotate(Tetrimino& tetrimino) const;
	void ClearFieldAndSaveLastPosition();
	void PlaceLastPositionOnField(const sf::Color tetriminoColor);
	void ClearFullRows();
	void Draw(sf::RenderWindow& wnd);
	
private:
	void ClearField();
	const bool NextMoveFree(int row, int colum, const Tetrimino& tetriminon) const;
	const bool RowIsFull(const int row) const;
	void ClearRow(const int row);
	void MoveAllRowsDown(const int row);

private:
	sf::Vector2f position;
	sf::RectangleShape frame;
	std::vector<Cell> cells;
	std::vector<Cell> firstRow;
	std::vector<int> lastPosition;
	
	const sf::Color backgroundColor = sf::Color::Transparent;

	static constexpr int columns = 10;
	static constexpr int rows = 24;

public:
	static constexpr int FrameThickness = 18;
	static constexpr int Width = columns * Cell::Dimensions;
	static constexpr int Height = rows * Cell::Dimensions;
	static constexpr int TotalWidth = 2 * FrameThickness + Width;
};

