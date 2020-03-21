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
	void HandleInput(sf::Event event);
	void Update(float dt);
	void Draw();

private:
	std::shared_ptr<GameData> gameData;
	TextBox gameOverTxtBox;
	Button newGameBtn;
	bool scoreSet = false;
	bool scoreHolderSet = false;
	bool switchColor = true;
	int newScoreindex = 0;
	float lastFlash = 0.f;
	std::string scoreHolder = "";
	std::vector<std::pair<std::string, unsigned int>> highScores;
	std::vector<sf::Text> scoreTexts;
	static constexpr char letters[27] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	static constexpr float flashTime = 0.3f;
};

