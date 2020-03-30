#pragma once
#include "IGuiElement.h"
#include "Game.h"
#include "HighScores.h"
#include "Button.h"
#include <fstream>

class GameOverState : public IState, public IGuiElement
{
public:
	GameOverState(std::shared_ptr<GameData> _gameData, const unsigned int score);

	void Init() override;
	void HandleInput() override;
	void HandleInput(const sf::Event& event) override;
	void Update(float dt) override;
	void Draw() override;

private:
	void SetupButtons(const sf::Font& font) override;
	void SetupTextBoxes(const sf::Font& font) override;
	void CheckButtonHover() override;
	void CheckButtonClick() override;
	void SetGuiElementPositions() override;

private:
	std::shared_ptr<GameData> gameData;
	TextBox gameOverTxtBox;
	Button newGameBtn;
	HighScores highScores;
	unsigned int newScore;
};

