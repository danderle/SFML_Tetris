#pragma once
#include "IGuiElement.h"
#include "Game.h"
#include "Field.h"
#include "Preview.h"

class PauseState : public IState, public IGuiElement
{
public:
	PauseState(std::shared_ptr<GameData> _gameData, const Field& _field, const std::vector<TextBox>& _textBoxes, const Preview& _preview);

	void Init() override;
	void HandleInput() override;
	void HandleInput(const sf::Event& event) override;
	void Update(float dt) override;
	void Draw() override;

private:
	void SetupTextBoxes(const sf::Font& font) override;
	void SetGuiElementPositions() override;

private:
	std::shared_ptr<GameData> gameData;
	Field field;
	std::vector<TextBox> textBoxes;
	Preview preview;
	TextBox pauseTxtBox;
};

