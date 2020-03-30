#pragma once
#include "SFML/Graphics.hpp"
#include "DEFINITIONS.h"
#include "IGuiElement.h"
#include <vector>
#include <sstream>
#include <fstream>

class HighScores : public IGuiElement
{
public:
	HighScores() = default;

	void Load();
	void SetNew(const unsigned int newScore);
	void SetupTop10List(const sf::Font& font);
	void AddCharToScoreHolder(const unsigned int keyCode);
	void RemoveCharFromScoreHolder();
	void SaveScoreHolder();
	bool IsNewScore() const;
	bool IsNewScoreSet() const;
	const float GetTopYPosition() const;
	const float GetBottomYPosition() const;
	void Flash(const float dt);
	void Draw(sf::RenderWindow& wnd);

	void SetGuiElementPositions() override;

private:
	std::vector<std::pair<std::string, unsigned int>> highScores;
	std::vector<sf::Text> highScoreTexts;
	sf::Text top10Text;

	unsigned int newScoreIndex = 0;
	std::string scoreHolder = "";
	bool scoreSet = false;
	bool isNewScore = false;
	bool isNewScoreSet = false;
	bool switchColor = true;
	float lastFlash = 0.f;

	static constexpr float flashTime = 0.3f;
	static constexpr char letters[27] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	static constexpr unsigned int maxHighScoresSize = 10;

};

