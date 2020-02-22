#pragma once

class Tetrimino
{
public:
	Tetrimino()
	{
	}

	void MoveDown()
	{
		rowPos += 1;
	}
	int GetRow() const
	{
		return rowPos;
	}
	int GetColumn() const
	{
		return colPos;
	}
	std::vector<std::vector<bool> > GetPosition() const
	{
		return cube;
	}
	sf::Color GetColor() const
	{
		return color;
	}
	void GetNext()
	{

	}
private:
	int rowPos = 0;
	int colPos = 5;
	std::vector<std::vector<bool> > cube = { {true ,true}, 
											{true ,true} };
	sf::Color color = sf::Color::Blue;
};

