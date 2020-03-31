#pragma once
#include "IGuiElement.h"
#include "Game.h"
#include "Button.h"
#include <sstream>

class SettingsState : public IState, public IGuiElement
{
public:
	SettingsState(std::shared_ptr<GameData> _gameData);

	void Init() override;
	void HandleInput() override;
	void HandleInput(const sf::Event& event) override;
	void Update(float dt) override;
	void Draw() override;

private:
	void SetupButtons(const sf::Font& font)  override;
	void SetGuiElementPositions() override;
	void CheckButtonHover() override;
	void CheckButtonClick(const sf::Event& event) override;
	void SetButtonState(Button& button, const bool on) override;

private:
	std::shared_ptr<GameData> gameData;
	Button musicBtn;
	Button soundBtn;
	Button backBtn;

	static constexpr float margin = 30.f;
};

