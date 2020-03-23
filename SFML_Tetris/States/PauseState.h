#pragma once
#include "Game.h"
#include "Field.h"
#include "Button.h"
#include "Preview.h"

class PauseState : public State
{
public:
	PauseState(std::shared_ptr<GameData> _gameData, const Field& _field, const std::vector<TextBox>& _textBoxes, const Preview& _preview);

	void Init();
	void HandleInput();
	void HandleInput(const sf::Event& event);
	void Update(float dt);
	void Draw();

private:
	void SetupButtons(const sf::Font& font);
	void SetupTextBoxes(const sf::Font& font);
	void CheckButtonHover();
	void CheckButtonClick();
	void SetGuiElementPositions();

private:
	std::shared_ptr<GameData> gameData;
	Field field;
	std::vector<TextBox> textBoxes;
	Preview preview;
	TextBox pauseTxtBox;
	Button resumeBtn;
};

