#pragma once
#include "IGuiElement.h"
#include "Game.h"
#include "HighScores.h"
#include <sstream>
#include <fstream>

class HighScoreState : public IState, public IGuiElement
{
public:
	HighScoreState() = delete;
	HighScoreState(std::shared_ptr<GameData> _gameData);

	void Init() override;
	void HandleInput() override;
	void HandleInput(const sf::Event& event) override;
	void Update(float dt) override;
	void Draw() override;

private:
	void SetupButtons(const sf::Font& font) override;
	void CheckButtonHover() override;
	void CheckButtonClick(const sf::Event& event) override;
	void SetGuiElementPositions() override;

private:
	std::shared_ptr<GameData> gameData;
	Button backBtn;
	HighScores highScores;
};

