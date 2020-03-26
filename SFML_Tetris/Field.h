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
	void UpdatePoints(unsigned int& currentScore, unsigned int& linesCleared, unsigned int& level);
	const bool FindFullRows();
	const bool IsFlashing() const;
	void FlashFullRows(const float dt);
	void Draw(sf::RenderWindow& wnd);

private:
	void ClearField();
	const bool NextMoveFree(int row, int colum, const Tetrimino& tetriminon) const;
	const bool RowIsFull(const int row) const;
	void SetRowUnoccupied(const int row);
	void MoveAllRowsDown();
	void MoveRowDown(const int row);

private:
	sf::Vector2f position;
	sf::RectangleShape frame;
	std::vector<Cell> cells;
	std::vector<Cell> firstRow;
	std::vector<int> lastPosition;
	std::vector<int> fullRows;
	const sf::Color backgroundColor = sf::Color::Transparent;
	sf::Color innerFlash = WHITE;
	sf::Color outerFlash = BLACK;
	bool foundFullRow = false;
	float totalFlashTime = 0.f;
	int colorChanger = 10;
	static constexpr float flashTime = 1.f;

public:
	static constexpr int Columns = 10;
	static constexpr int Rows = 24;
	static constexpr int GridSize = Rows * Columns;
	static constexpr int FrameThickness = 18;
	static constexpr int Width = Columns * Cell::Dimensions;
	static constexpr int Height = Rows * Cell::Dimensions;
	static constexpr int TotalWidth = 2 * FrameThickness + Width;
};

