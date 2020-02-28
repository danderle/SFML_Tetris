#include "TetriminoFactory.h"

TetriminoFactory::TetriminoFactory()
	:
	rng(rnd())
{
	colorIndex = std::uniform_int_distribution<int>(0, colors.size() - 1);
	typeIndex = std::uniform_int_distribution<int>(0, types.size() - 1);
}

std::unique_ptr<Tetrimino> TetriminoFactory::CreateTetrimino()
{
	int cIndex = colorIndex(rng);
	int tIndex = typeIndex(rng);
	return std::make_unique<Tetrimino>(types[tIndex], colors[cIndex]);
}
