#pragma once
#include "SFML/Graphics.hpp"
#include "Tetrimino.h"
#include <random>
#include <vector>

class TetriminoFactory
{
public:
	TetriminoFactory();

	std::unique_ptr<Tetrimino> CreateTetrimino();

private:
	std::random_device rnd;
    std::mt19937 rng;
    std::uniform_int_distribution<int> colorIndex;
    std::uniform_int_distribution<int> typeIndex; 
	
	const sf::Color red = sf::Color::Red;
	const sf::Color green = sf::Color::Green;
	const sf::Color blue = sf::Color::Blue;
	const sf::Color magenta = sf::Color::Magenta;
	const sf::Color cyan = sf::Color::Cyan;
	const sf::Color yellow = sf::Color::Yellow;
	const std::vector<sf::Color> colors = {red, green, blue, magenta, cyan, yellow};

	const std::vector<std::vector<bool>> Otetri = { {true, true},
													{true, true} };

	const std::vector<std::vector<bool>> Itetri = { {true,  true,  true,  true} };

	const std::vector<std::vector<bool>> Jtetri = { {true, false, false},
													{true, true,  true} };

	const std::vector<std::vector<bool>> Ltetri = { {true, true,  true},
													{true, false, false} };

	const std::vector<std::vector<bool>> Stetri = { {false, true, true},
													{true,  true, false} };

	const std::vector<std::vector<bool>> Ttetri = { {false, true, false},
													{true,  true, true} };

	const std::vector<std::vector<bool>> Ztetri = { {true,  true, false},
													{false, true, true} };

	const std::vector<std::vector<std::vector<bool>>> types = { Otetri , Itetri, Jtetri, Ltetri, Stetri, Ttetri, Ztetri };
};

