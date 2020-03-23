#include "PauseState.h"

PauseState::PauseState(std::shared_ptr<GameData> _gameData, const Field& _field, const std::vector<TextBox>& _textBoxes, const Preview& _preview)
	:
	gameData(_gameData),
	field(_field),
	textBoxes(_textBoxes),
	preview(_preview),
	resumeBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	pauseTxtBox(TEXTBOX_WIDTH, TEXTBOX_HEIGHT)
{
	auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	resumeBtn.SetFont(font, CHARACTER_SIZE);
	resumeBtn.SetOutline(GREEN, OUTLINE_THICKNESS);
	resumeBtn.SetContent("Continue", Alignment::CENTER);
	resumeBtn.SetTextColor(GREEN);
	resumeBtn.CenterText();
	resumeBtn.SetPosition({ WINDOW_WIDTH - resumeBtn.GetRect().width, 0 });
	pauseTxtBox.SetFont(font, CHARACTER_SIZE);
	pauseTxtBox.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	pauseTxtBox.SetContent("GAME PAUSED", Alignment::CENTER);
	pauseTxtBox.SetTextColor(BLACK);
	pauseTxtBox.SetOutline(BLACK, OUTLINE_THICKNESS);
}

void PauseState::Init()
{
}

void PauseState::HandleInput()
{
	resumeBtn.MouseHoverEffect(gameData->input.IsHovering(resumeBtn.GetRect(), gameData->window));
	bool isClicked = gameData->input.IsRectClicked(resumeBtn.GetRect(), sf::Mouse::Left, gameData->window);
	if (isClicked)
	{
		gameData->machine.RemoveState();
	}
}

void PauseState::HandleInput(const sf::Event& event)
{
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
	resumeBtn.Draw(gameData->window);
	gameData->window.display();
}
