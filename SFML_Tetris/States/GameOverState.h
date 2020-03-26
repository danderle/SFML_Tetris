#pragma once
#include "Game.h"
#include "State.h"
#include "Button.h"
#include <fstream>

class GameOverState : public State
{
public:
	GameOverState(std::shared_ptr<GameData> _gameData, const unsigned int score);

	void Init();
	void HandleInput();
	void HandleInput(const sf::Event& event);
	void Update(float dt);
	void Draw();

private:
	void SetupTextBoxes(const sf::Font& font);
	void LoadHighScores();
	void SetNewHighScore();
	void SetupHighScoreTexts(const sf::Font& font);
	void SetupButtons(const sf::Font& font);
	void SetGuiElementPositions();
	void CheckButtonHover();
	void CheckButtonClick();

private:
	std::shared_ptr<GameData> gameData;
	TextBox gameOverTxtBox;
	Button newGameBtn;
	sf::Text top10Text;
	unsigned int newScore;
	bool scoreSet = false;
	bool scoreHolderSet = false;
	bool saveNewScore = false;
	bool switchColor = true;
	unsigned int newScoreindex = 0;
	float lastFlash = 0.f;
	std::string scoreHolder = "";
	std::vector<std::pair<std::string, unsigned int>> highScores;
	std::vector<sf::Text> scoreTexts;
	static constexpr char letters[27] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	static constexpr float flashTime = 0.3f;
	static constexpr unsigned int maxHighScoresSize = 10;
};

