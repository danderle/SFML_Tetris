#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include <iostream>

//// initialize TetriminoFactory one time
TetriminoFactory GameState::factory;

GameState::GameState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	field({(float)Field::FrameThickness, gameData->window.getSize().y - (float)(Field::Height + Field::FrameThickness)}),
	scoreTxtBox( WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 6, BLACK),
	nextTxtBox(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 4, BLACK),
	linesClearedTxtBox(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 6, BLACK),
	droughtTxtBox(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 6, BLACK),
	levelTxtBox(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 6, BLACK),
	preview(nextTxtBox)
{
}

void GameState::Init()
{
	SetupTextBox();
	SetGuiElementPositions();
	CreateNextTetrimino();
	GetNextTetrimino();
	CreateNextTetrimino();
	gameData->assets.StartMusic(THEME_SOUND_PATH);
}

void GameState::HandleInput()
{
}

void GameState::HandleInput(const sf::Event& event)
{
	if (gameOver)
	{
		return;
	}
	if (event.key.code == sf::Keyboard::A)
	{
		tetrimino->RotateLeft();
		if (!field.CanRotate(*tetrimino))
		{
			tetrimino->RotateRight();
		}
		else
		{
			gameData->assets.PlaySound(SELECTION_SOUND);
		}
	}
	else if (event.key.code == sf::Keyboard::D)
	{
		tetrimino->RotateRight();
		if (!field.CanRotate(*tetrimino))
		{
			tetrimino->RotateLeft();
		}
		else
		{
			gameData->assets.PlaySound(SELECTION_SOUND);
		}
	}
	else if (event.key.code == sf::Keyboard::Left)
	{
		if (field.CanMoveLeft(*tetrimino))
		{
			tetrimino->MoveLeft();
			gameData->assets.PlaySound(FALL_SOUND);
		}
	}
	else if (event.key.code == sf::Keyboard::Right)
	{
		if (field.CanMoveRight(*tetrimino))
		{
			tetrimino->MoveRight();
			gameData->assets.PlaySound(FALL_SOUND);
		}
	}
	else if (event.key.code == sf::Keyboard::Key::Down)
	{
		if (!field.IsFlashing())
		{
			moveTimePassed = 0;
			field.ShowOnField(*tetrimino);
			MoveTetriminoOrPlaceOnField();
		}
	}
	else if (gameData->input.KeyHit(sf::Keyboard::Key::Space))
	{
		CopyTextBoxesAndOpenPauseState();
	}
}

void GameState::Update(float dt)
{
	if (!gameOver)
	{
		if (field.IsFlashing())
		{
			field.FlashFullRows(dt);
		}
		else
		{
			field.ShowOnField(*tetrimino);
			moveTimePassed += dt;
			if (moveTimePassed > fallingSpeed)
			{
				moveTimePassed = 0;
				MoveTetriminoOrPlaceOnField();
			}
		}
	}
	else
	{
		if (!gameData->assets.SoundStillPlaying(GAMEOVER_SOUND))
		{
			gameData->machine.AddState(std::make_unique<GameOverState>(gameData, currentScore));
		}
	}
}

void GameState::Draw()
{
	gameData->window.clear();

	field.Draw(gameData->window);

	scoreTxtBox.Draw(gameData->window);
	nextTxtBox.Draw(gameData->window);
	linesClearedTxtBox.Draw(gameData->window);
	droughtTxtBox.Draw(gameData->window);
	levelTxtBox.Draw(gameData->window);
	preview.Draw(gameData->window);

	gameData->window.display();
}


//// **** Private Functions ****

void GameState::MoveTetriminoOrPlaceOnField()
{
	if (field.CanMoveDown(*tetrimino))
	{
		tetrimino->MoveDown();
		gameData->assets.PlaySound(FALL_SOUND);
	}
	else
	{
		if (tetrimino->GetRow() == Tetrimino::StartingRow)
		{
			gameData->assets.StopMusic();
			gameOver = true;
			gameData->assets.PlaySound(GAMEOVER_SOUND);
			return;
		}
		field.ClearFieldAndSaveLastPosition();
		field.PlaceLastPositionOnField(tetrimino->GetColor());
		if (field.FindFullRows())
		{
			auto numOfRows = field.NumberOfClearedRows();
			linesCleared += numOfRows;
			LevelUp();
			AddPoints(numOfRows);
			if (numOfRows == 4)
			{
				gameData->assets.PlaySound(TETRIS_SOUND);
			}
			else
			{
				gameData->assets.PlaySound(LINE_SOUND);
			}
			UpdateTextBox();
		}
		GetNextTetrimino();
		CreateNextTetrimino();
	}
}

void GameState::SetupTextBox()
{
	const auto& font = gameData->assets.GetFont(UNISPACE_FONT);
	float outlineThickness = -15;
	unsigned int charSize = 20;
	scoreTxtBox.SetFont(font, charSize);
	std::string text = "SCORE";
	scoreTxtBox.SetOutlineColor(LIGHTGRAY, outlineThickness);
	scoreTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(currentScore);
	scoreTxtBox.SetContent(text, Alignment::CENTER);
	
	nextTxtBox.SetFont(font, charSize);
	text = "NEXT";
	nextTxtBox.SetOutlineColor(LIGHTGRAY, outlineThickness);
	nextTxtBox.SetContent(text, Alignment::TOP);

	linesClearedTxtBox .SetFont(font, charSize);
	text = "LINES CLEARED";
	linesClearedTxtBox.SetOutlineColor(LIGHTGRAY, outlineThickness);
	linesClearedTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(linesCleared);
	linesClearedTxtBox.SetContent(text, Alignment::CENTER);
	
	droughtTxtBox.SetFont(font, charSize);
	text = "DROUGHT";
	droughtTxtBox.SetOutlineColor(LIGHTGRAY, outlineThickness);
	droughtTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(droughtCount);
	droughtTxtBox.SetContent(text, Alignment::CENTER);

	levelTxtBox.SetFont(font, charSize);
	text = "LEVEL";
	levelTxtBox.SetOutlineColor(LIGHTGRAY, outlineThickness);
	levelTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(level);
	levelTxtBox.SetContent(text, Alignment::CENTER);
}

void GameState::LevelUp()
{
	level = linesCleared / 10;
	level = level == 0 ? 1 : level;
	fallingSpeed = startSpeed - (0.03f * level);
}

void GameState::AddPoints(const unsigned int numOfClearedRows)
{
	switch (numOfClearedRows)
	{
	case 1:
		currentScore += 40 * level;
		break;
	case 2:
		currentScore += 100 * level;
		break;
	case 3:
		currentScore += 300 * level;
		break;
	case 4:
		currentScore += 1200 * level;
		break;
	default:
		currentScore += 0;
	}
}

void GameState::UpdateTextBox()
{
	scoreTxtBox.SetContent(std::to_string(currentScore), Alignment::CENTER);
	linesClearedTxtBox.SetContent(std::to_string(linesCleared), Alignment::CENTER);
	droughtTxtBox.SetContent(std::to_string(droughtCount), Alignment::CENTER);
	levelTxtBox.SetContent(std::to_string(level), Alignment::CENTER);
}

void GameState::GetNextTetrimino()
{
	tetrimino = std::move(nextTetrimino);
	droughtCount += tetrimino->IsI() ? -1 * droughtCount : 1;
	if (droughtCount > 15)
	{
		droughtTxtBox.SetTextColor(RED);
	}
	else
	{
		droughtTxtBox.SetTextColor(WHITE);
	}
	droughtTxtBox.SetContent(std::to_string(droughtCount), Alignment::CENTER);
}

void GameState::CreateNextTetrimino()
{
	nextTetrimino = factory.CreateTetrimino();
	preview.SetNext(*nextTetrimino);
	preview.Center();
}

void GameState::CopyTextBoxesAndOpenPauseState()
{
	std::vector<TextBox> textBoxes;
	textBoxes.push_back(scoreTxtBox);
	textBoxes.push_back(nextTxtBox);
	textBoxes.push_back(linesClearedTxtBox);
	textBoxes.push_back(droughtTxtBox);
	textBoxes.push_back(levelTxtBox);
	gameData->machine.AddState(std::make_unique<PauseState>(gameData, field, textBoxes, preview), false);
	/*gameData->assets.StopMusic();
	gameData->assets.PlaySound(GAMEOVER_SOUND);
	gameOver = true;*/
}

void GameState::SetGuiElementPositions()
{
	scoreTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, 25 });
	float yPos = scoreTxtBox.GetPosition().y + scoreTxtBox.GetRect().height + TextBox::Margin;
	nextTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos });
	yPos = nextTxtBox.GetPosition().y + nextTxtBox.GetRect().height + TextBox::Margin;
	linesClearedTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos });
	yPos = linesClearedTxtBox.GetPosition().y + linesClearedTxtBox.GetRect().height + TextBox::Margin;
	droughtTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos });
	yPos = droughtTxtBox.GetPosition().y + droughtTxtBox.GetRect().height + TextBox::Margin;
	levelTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos });

}
