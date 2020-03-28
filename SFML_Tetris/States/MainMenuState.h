#pragma once
#include "Game.h"
#include "State.h"
#include "Button.h"

class MainMenuState : public State
{
public:
	MainMenuState() = delete;
	MainMenuState(std::shared_ptr<GameData> _gameData);

	void Init();
	void HandleInput();
	void HandleInput(const sf::Event& event);
	void Update(float dt);
	void Draw();

private:
	void SetupButtons(const sf::Font& font);
	void CheckButtonHover();
	void CheckButtonClick();
	void SetGuiElementPositions();

private:
	std::shared_ptr<GameData> gameData;
	Button playButton;
	Button settingsBtn;
	Button highScoresBtn;

	static constexpr float margin = 30.f;

};

