#pragma once
#include "Game.h"
#include "State.h"
#include "Field.h"
#include "TetriminoFactory.h"
#include "TextBox.h"

class GameState : public State
{
public:
	GameState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void HandleInput(sf::Event event);
	void Update(float dt);
	void Draw();

private:
	void MoveTetriminoOrPlaceOnField();

private:
	static TetriminoFactory factory;
	std::shared_ptr<GameData> gameData;
	Field field;
	TextBox scoreBoard;
	TextBox nextTetri;
	TextBox linesCleared;
	std::unique_ptr<Tetrimino> tetrimino;
	std::unique_ptr<Tetrimino> nextTetrimino;
	float autoTimePassed = 0;
	float manualTimePassed = 0;
	static constexpr float autoMoveTime = 0.5f;
	static constexpr float manualMoveTime = 0.1f;
	std::vector<std::vector<bool> > tetri = { {true ,true},
											  {true ,true} };
};
