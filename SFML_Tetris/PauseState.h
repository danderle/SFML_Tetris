#pragma once
#include "Game.h"
#include "Field.h"
#include "Button.h"
#include <Preview.h>

class PauseState : public State
{
public:
	PauseState(std::shared_ptr<GameData> _gameData, const Field& _field, const std::vector<TextBox>& _textBoxes, const Preview& _preview);

	void Init();
	void HandleInput();
	void HandleInput(sf::Event event);
	void Update(float dt);
	void Draw();

private:
	std::shared_ptr<GameData> gameData;
	Field field;
	std::vector<TextBox> textBoxes;
	Preview preview;
	TextBox pauseTxtBox;
	Button resumeBtn;
};

