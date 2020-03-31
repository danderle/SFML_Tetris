#include "GameOverState.h"
#include "MainMenuState.h"
#include <sstream>
GameOverState::GameOverState(std::shared_ptr<GameData> _gameData, const unsigned int _newScore)
:
	gameData(_gameData),
	gameOverTxtBox(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	newGameBtn(TEXTBOX_WIDTH, TEXTBOX_HEIGHT),
	newScore(_newScore)
{
}

void GameOverState::Init()
{
	highScores.Load();
	highScores.SetNew(newScore);
	if (highScores.IsNewScore())
	{
		newGameBtn.Disable();
	}
	auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	highScores.SetupTop10List(font);
	SetupTextBoxes(font);
	SetupButtons(font);
	SetGuiElementPositions();
}

void GameOverState::HandleInput()
{
	CheckButtonHover();
}

void GameOverState::HandleInput(const sf::Event& event)
{
	if(highScores.IsNewScore())
	{
		if (!highScores.IsNewScoreSet() && gameData->input.KeyReleased(event, sf::Keyboard::Backspace))
		{
			highScores.RemoveCharFromScoreHolder();
		}
		else if (!highScores.IsNewScoreSet() && gameData->input.KeyReleased(event, sf::Keyboard::Enter))
		{
			highScores.SaveScoreHolder();
			newGameBtn.Enable();
		}
		else if (!highScores.IsNewScoreSet() && event.KeyReleased)
		{
			highScores.AddCharToScoreHolder(event.key.code);
		}
	}
	else
	{
		CheckButtonClick(event);
	}
}

void GameOverState::Update(float dt)
{
	highScores.Flash(dt);
}

void GameOverState::Draw()
{
	  
	gameData->window.clear();
	newGameBtn.Draw(gameData->window);
	gameOverTxtBox.Draw(gameData->window);
	highScores.Draw(gameData->window);
	gameData->window.display();
}

//// **** Private Functions ****

void GameOverState::SetupButtons(const sf::Font& font)
{
	newGameBtn.SetTemplate(font, "Main Menu");
}

void GameOverState::SetupTextBoxes(const sf::Font& font)
{
	gameOverTxtBox.SetFont(font, CHARACTER_SIZE);
	gameOverTxtBox.SetContent("GAME OVER", Alignment::CENTER);
	gameOverTxtBox.SetCenterAt({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	gameOverTxtBox.SetTextColor(BLACK);
	gameOverTxtBox.SetOutlineColor(BLACK, OUTLINE_THICKNESS);
}


void GameOverState::CheckButtonHover()
{
	newGameBtn.MouseHoverEffect(gameData->input.IsHovering(newGameBtn.GetRect(), gameData->window));
}

void GameOverState::CheckButtonClick(const sf::Event& event)
{
	if (newGameBtn.IsEnabled())
	{
		if (event.mouseButton.button == sf::Mouse::Left &&
			gameData->input.IsRectClicked(newGameBtn.GetRect(), gameData->window))
		{
			gameData->machine.AddState(std::make_unique<MainMenuState>(gameData));
		}
	}
}

void GameOverState::SetGuiElementPositions()
{
	highScores.SetGuiElementPositions();

	float padding = 20.f;
	float yStartPosition = highScores.GetTopYPosition() - padding - TEXTBOX_HEIGHT;
	gameOverTxtBox.SetPosition({ (WINDOW_WIDTH - TEXTBOX_WIDTH) / 2, yStartPosition });

	yStartPosition = highScores.GetBottomYPosition() + padding * 2;
	newGameBtn.SetPosition({ gameOverTxtBox.GetPosition().x, yStartPosition });
}