#pragma once
#include "IGuiElement.h"
#include "Game.h"
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
	void CheckButtonClick() override;
	void SetGuiElementPositions() override;
	void LoadHighScores();
	void SetupHighScoreTexts(const sf::Font& font);

protected:
	std::shared_ptr<GameData> gameData;
	std::vector<std::pair<std::string, unsigned int>> highScores;
	std::vector<sf::Text> highScoreTexts;

private:
	Button backBtn;
	sf::Text top10Text;
};

