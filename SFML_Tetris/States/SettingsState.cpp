#include "SettingsState.h"
#include "MainMenuState.h"

SettingsState::SettingsState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	musicBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	soundBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	backBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT)
{
}

void SettingsState::Init()
{
	const auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	SetupButtons(font);
	SetGuiElementPositions();
}

void SettingsState::HandleInput()
{
	CheckButtonHover();
	CheckButtonClick();
}

void SettingsState::HandleInput(const sf::Event& event)
{
	CheckButtonClick(event);
}

void SettingsState::Update(float dt)
{
}

void SettingsState::Draw()
{
	gameData->window.clear();
	musicBtn.Draw(gameData->window);
	soundBtn.Draw(gameData->window);
	backBtn.Draw(gameData->window);
	gameData->window.display();
}

void SettingsState::SetupButtons(const sf::Font& font)
{
	musicBtn.SetTemplate(font, "Music On");
	soundBtn.SetTemplate(font, "Sound On");
	backBtn.SetTemplate(font, "Back");
	SetButtonState(musicBtn, gameData->assets.MusicOn());
	SetButtonState(soundBtn, gameData->assets.SoundsOn());
}

void SettingsState::SetGuiElementPositions()
{
	musicBtn.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3 });
	musicBtn.CenterText();

	auto previousBtnPos = musicBtn.GetPosition();
	soundBtn.SetPosition(previousBtnPos.x, previousBtnPos.y + musicBtn.GetRect().height + margin);
	backBtn.SetPosition({ WINDOW_WIDTH - backBtn.GetRect().width, 0 });
}

void SettingsState::CheckButtonHover()
{
	bool isHovering = gameData->input.IsHovering(musicBtn.GetRect(), gameData->window);
	musicBtn.MouseHoverEffect(isHovering);
	isHovering = gameData->input.IsHovering(soundBtn.GetRect(), gameData->window);
	soundBtn.MouseHoverEffect(isHovering);
	isHovering = gameData->input.IsHovering(backBtn.GetRect(), gameData->window);
	backBtn.MouseHoverEffect(isHovering);
}

void SettingsState::CheckButtonClick()
{
	bool isClicked = gameData->input.IsRectClicked(backBtn.GetRect(), sf::Mouse::Left, gameData->window);
	if (isClicked)
	{
		gameData->machine.AddState(std::make_unique<MainMenuState>(gameData));
	}
}

void SettingsState::CheckButtonClick(const sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		bool isClicked = gameData->input.IsRectClicked(musicBtn.GetRect(), gameData->window);
		if (isClicked)
		{
			const float volume = gameData->assets.MusicOn() ? 0 : 100;
			gameData->assets.SetMusicVolume(volume);
			SetButtonState(musicBtn, gameData->assets.MusicOn());
		}
		isClicked = gameData->input.IsRectClicked(soundBtn.GetRect(), gameData->window);
		if (isClicked)
		{
			const float volume = gameData->assets.SoundsOn() ? 0 : 100;
			gameData->assets.SetSoundsVolume(volume);
			SetButtonState(soundBtn, gameData->assets.SoundsOn());
		}
	}
}

void SettingsState::SetButtonState(Button& button, const bool on)
{
	std::stringstream ss;
	ss << button.GetContent(Alignment::CENTER);
	std::string content;
	ss >> content;
	if (on)
	{
		content += " On";
		button.SetBackColor(GREEN);
		button.SetOutlineColor(GREEN, OUTLINE_THICKNESS);
	}
	else
	{
		content += " Off";
		button.SetBackColor(DARKORANGE);
		button.SetOutlineColor(DARKORANGE, OUTLINE_THICKNESS);
	}
	button.SetContent(content, Alignment::CENTER);
}
