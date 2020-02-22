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

	void ShowOnField(const Tetrimino& tetrimino);
	void Draw(sf::RenderWindow& wnd);
	
private:
	void PlaceOnField(const std::vector<int>& lastPosition, const sf::Color color);
	const std::vector<int>& ClearFieldAndSaveLastPosition(int lastPosition);

private:
	sf::Vector2f position;
	std::vector<Cell> cells;
	static constexpr int width = 10;
	static constexpr int height = 24;
};

