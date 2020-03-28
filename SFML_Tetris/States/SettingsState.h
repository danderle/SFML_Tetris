#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"
#include <sstream>

class SettingsState : public State
{
public:
	SettingsState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void HandleInput(const sf::Event& event);
	void Update(float dt);
	void Draw();

private:
	void SetupButtons(const sf::Font& font);
	void SetGuiElementPositions();
	void CheckButtonHover();
	void CheckButtonClick();
	void CheckButtonClick(const sf::Event& event);
	void SetButtonState(Button& button, const bool on);

private:
	std::shared_ptr<GameData> gameData;
	Button musicBtn;
	Button soundBtn;
	Button backBtn;

	static constexpr float margin = 30.f;
};

