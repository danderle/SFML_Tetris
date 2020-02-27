#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
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
	void ClearFieldAndSaveLastPosition();
	void PlaceLastPositionOnField(const sf::Color tetriminoColor);
	void Draw(sf::RenderWindow& wnd);
	
private:
	void ClearField();
	const bool NextMoveFree(int row, int colum, const Tetrimino& tetriminon) const;

private:
	sf::Vector2f position;
	std::vector<Cell> cells;
	std::vector<int> lastPosition;
	static constexpr int width = 10;
	static constexpr int height = 24;
};

