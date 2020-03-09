#pragma once
#include "Game.h"
#include "State.h"
#include "Field.h"
#include "TetriminoFactory.h"
#include "TextBox.h"
#include "Preview.h"

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
	void SetupTextBox();
	void UpdateTextBox();

private:
	static TetriminoFactory factory;
	std::shared_ptr<GameData> gameData;
	Field field;
	TextBox scoreTxtBox;
	TextBox nextTxtBox;
	TextBox linesClearedTxtBox;
	TextBox droughtTxtBox;
	TextBox levelTxtBox;
	std::unique_ptr<Tetrimino> tetrimino;
	std::unique_ptr<Tetrimino> nextTetrimino;
	Preview preview;
	unsigned int currentScore = 0;
	unsigned int linesCleared = 0;
	unsigned int level = 1;
	unsigned int iDroughtCount = 0;

	float autoTimePassed = 0;
	float manualTimePassed = 0;
	float fallingSpeed = startSpeed;
	
	static constexpr float startSpeed = 0.83f;
	static constexpr float manualMoveTime = 0.1f;
};
