#pragma once
#include "IGuiElement.h"
#include "Game.h"
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
	void LoadHighScores();
	void SetNewHighScore();
	void SetupHighScoreTexts(const sf::Font& font);

private:
	std::shared_ptr<GameData> gameData;
	TextBox gameOverTxtBox;
	Button newGameBtn;
	sf::Text top10Text;
	sf::Clock clock;
	unsigned int newScore;
	bool scoreSet = false;
	bool scoreHolderSet = false;
	bool saveNewScore = false;
	bool switchColor = true;
	unsigned int newScoreIndex = 0;
	float lastFlash = 0.f;
	std::string scoreHolder = "";
	std::vector<std::pair<std::string, unsigned int>> highScores;
	std::vector<sf::Text> scoreTexts;
	static constexpr char letters[27] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	static constexpr float flashTime = 0.3f;
	static constexpr unsigned int maxHighScoresSize = 10;
};

