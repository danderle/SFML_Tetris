#pragma once
#include "Game.h"
#include "IState.h"
#include "IGuiElement.h"
#include "Field.h"
#include "TetriminoFactory.h"
#include "TextBox.h"
#include "Preview.h"

class GameState : public IState, public IGuiElement
{
public:
	GameState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void HandleInput(const sf::Event& event);
	void Update(float dt);
	void Draw();

private:
	void MoveTetriminoOrPlaceOnField();
	void SetupTextBox();
	void LevelUp();
	void AddPoints(const unsigned int numOfClearedRows);
	void UpdateTextBox();
	void GetNextTetrimino();
	void CreateNextTetrimino();
	void CopyTextBoxesAndOpenPauseState();

	void SetGuiElementPositions() override;

private:
	std::shared_ptr<GameData> gameData;
	static TetriminoFactory factory;
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
	unsigned int droughtCount = 0;
	bool gameOver = false;
	float moveTimePassed = 0;
	float fallingSpeed = startSpeed;
	
	static constexpr float startSpeed = 0.83f;
	static constexpr float manualMoveTime = 0.1f;
	static constexpr float moveDownTimeOut = 5.f;
};
