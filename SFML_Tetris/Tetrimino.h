#pragma once
#include "SFML/Graphics.hpp"
#include <random>
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
	int GetWidth() const;
	int GetHeight() const;
	std::vector<std::vector<bool> > GetPosition() const;
	sf::Color GetColor() const;

private:
	int rowPos;
	int colPos;
	std::vector<std::vector<bool>> tetri;
	sf::Color color;
	std::random_device rnd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> colorIndex;
	std::uniform_int_distribution<int> typeIndex;

	static constexpr int maxColumns = 10;
	const sf::Color red = sf::Color::Red;
	const sf::Color green = sf::Color::Green;
	const sf::Color blue = sf::Color::Blue;
	const sf::Color magenta = sf::Color::Magenta;
	const sf::Color cyan = sf::Color::Cyan;
	const sf::Color yellow = sf::Color::Yellow;
	const sf::Color colors[6] = { red, green, blue, magenta, cyan, yellow };

	std::vector<std::vector<bool> > Otetri = { {true, true},
											   {true, true} };

	std::vector<std::vector<bool> > Itetri = { {true,  true,  true,  true},
											   {false, false, false, false} };

	std::vector<std::vector<bool> > Jtetri = { {true, false, false},
											   {true, true,  true} };

	std::vector<std::vector<bool> > Ltetri = { {true, true,  true},
											   {true, false, false} };

	std::vector<std::vector<bool> > Stetri = { {false, true, true},
											   {true,  true, false} };

	std::vector<std::vector<bool> > Ttetri = { {false, true, false},
											   {true,  true, true} };

	std::vector<std::vector<bool> > Ztetri = { {true,  true, false},
											   {false, true, true} };

	const std::vector<std::vector<std::vector<bool>>> types = { Otetri , Itetri, Jtetri, Ltetri, Stetri, Ttetri, Ztetri };
};

