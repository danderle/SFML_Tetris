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
	void SetupScoreTextBox(const sf::Font& font);
	void SetupNextTextBox(const sf::Font& font);

private:
	static TetriminoFactory factory;
	std::shared_ptr<GameData> gameData;
	Field field;
	TextBox scoreTxtBox;
	TextBox nextTxtBox;
	TextBox linesCleared;
	std::unique_ptr<Tetrimino> tetrimino;
	std::unique_ptr<Tetrimino> nextTetrimino;
	Preview preview;
	int currentScore = 0;
	float autoTimePassed = 0;
	float manualTimePassed = 0;
	
	static constexpr float autoMoveTime = 0.5f;
	static constexpr float manualMoveTime = 0.1f;
};
