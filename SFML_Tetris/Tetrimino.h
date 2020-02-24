#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Tetrimino
{
public:
	Tetrimino() = delete;
	Tetrimino(std::vector<std::vector<bool>> type, sf::Color _color);

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	int GetRow() const;
	int GetColumn() const;
	std::vector<std::vector<bool> > GetPosition() const;
	sf::Color GetColor() const;
	void PlacedOnField();
	const bool IsPlacedOnField() const;
	

private:
	int rowPos;
	int colPos;
	std::vector<std::vector<bool>> tetri;
	sf::Color color;
	bool isPlacedOnField = false;
	static constexpr int maxColumns = 10;
};

