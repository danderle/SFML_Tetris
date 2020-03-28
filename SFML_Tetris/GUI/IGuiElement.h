#pragma once
#include "Button.h"

class IGuiElement
{
public:
	virtual void SetupButtons(const sf::Font& font) {};
	virtual void SetupTextBoxes(const sf::Font& font) {};
	virtual void SetButtonState(Button& button, const bool on) {};
	virtual void CheckButtonHover() {};
	virtual void CheckButtonClick() {};
	virtual void CheckButtonClick(const sf::Event& event) {};
	virtual void SetGuiElementPositions() = 0;
};

