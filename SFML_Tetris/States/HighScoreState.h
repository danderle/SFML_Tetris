#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"
#include <sstream>
#include <fstream>

class HighScoreState : public State
{
public:
	HighScoreState() = delete;
	HighScoreState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void HandleInput(const sf::Event& event);
	void Update(float dt);
	void Draw();

private:
	void SetupButtons(const sf::Font& font);
	void LoadHighScores();
	void CheckButtonHover();
	void CheckButtonClick();
	void SetupHighScoreTexts(const sf::Font& font);
	void SetGuiElementPositions();

protected:
	std::shared_ptr<GameData> gameData;
	std::vector<std::pair<std::string, unsigned int>> highScores;
	std::vector<sf::Text> highScoreTexts;

private:
	Button backBtn;
	sf::Text top10Text;
};

