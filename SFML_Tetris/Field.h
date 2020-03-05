#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <algorithm>
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
	
	const sf::Color background = sf::Color::Transparent;

	static constexpr int width = 10;
	static constexpr int height = 24;
};

