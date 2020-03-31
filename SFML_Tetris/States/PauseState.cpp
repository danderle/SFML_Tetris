#include "PauseState.h"

PauseState::PauseState(std::shared_ptr<GameData> _gameData, const Field& _field, const std::vector<TextBox>& _textBoxes, const Preview& _preview)
	:
	gameData(_gameData),
	field(_field),
	textBoxes(_textBoxes),
	preview(_preview),
	pauseTxtBox(TEXTBOX_WIDTH, TEXTBOX_HEIGHT)
{
}

void PauseState::Init()
{
	auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	SetupTextBoxes(font);
	SetGuiElementPositions();
}

void PauseState::HandleInput()
{
}

void PauseState::HandleInput(const sf::Event& event)
{
	if (gameData->input.KeyHit(sf::Keyboard::Key::Space))
	{
		gameData->machine.RemoveState();
	}
}

void PauseState::Update(float dt)
{
}

void PauseState::Draw()
{
	gameData->window.clear();
	field.Draw(gameData->window);
	for (auto txtbox : textBoxes)
	{
		txtbox.Draw(gameData->window);
	}
	preview.Draw(gameData->window);
	pauseTxtBox.Draw(gameData->window);
	gameData->window.display();
}

void PauseState::SetupTextBoxes(const sf::Font& font)
{
	pauseTxtBox.SetFont(font, CHARACTER_SIZE);
	pauseTxtBox.SetContent("GAME PAUSED", Alignment::CENTER);
	pauseTxtBox.SetTextColor(BLACK);
	pauseTxtBox.SetOutlineColor(BLACK, OUTLINE_THICKNESS);
}

void PauseState::SetGuiElementPositions()
{
	pauseTxtBox.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
}
