#pragma once
#include "SFML/Graphics.hpp"
#include <random>
#include <vector>

class Tetrimino
{
public:
	Tetrimino() = delete;
	Tetrimino(std::vector<std::vector<bool>> _type, sf::Color _color);

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	int GetRow() const;
	int GetColumn() const;
	int GetWidth() const;
	int GetHeight() const;
	std::vector<std::vector<bool> > GetPosition() const;
	sf::Color GetColor() const;

private:
	int rowPos;
	int colPos;
	std::vector<std::vector<bool>> type;
	sf::Color color;
	static constexpr int maxColumns = 10;
};

