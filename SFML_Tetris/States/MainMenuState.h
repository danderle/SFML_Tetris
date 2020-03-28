#pragma once
#include "IGuiElement.h"
#include "Game.h"

class MainMenuState : public IState, public IGuiElement
{
public:
	MainMenuState() = delete;
	MainMenuState(std::shared_ptr<GameData> _gameData);

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

private:
	std::shared_ptr<GameData> gameData;
	Button playButton;
	Button settingsBtn;
	Button highScoresBtn;

	static constexpr float margin = 30.f;
};

