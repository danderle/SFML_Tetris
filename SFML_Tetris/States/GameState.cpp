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
	CreateNextTetrimino();
	GetNextTetrimino();
	CreateNextTetrimino();
}

void GameState::HandleInput()
{
}

void GameState::HandleInput(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::A)
	{
		tetrimino->RotateLeft();
		if (!field.CanRotate(*tetrimino))
		{
			tetrimino->RotateRight();
		}
		else
		{
			gameData->assets.GetSound(SELECTION_SOUND).play();
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
			gameData->assets.GetSound(SELECTION_SOUND).play();
		}
	}
	else if (event.key.code == sf::Keyboard::Left)
	{
		if (field.CanMoveLeft(*tetrimino))
		{
			tetrimino->MoveLeft();
			gameData->assets.GetSound(FALL_SOUND).play();
		}
	}
	else if (event.key.code == sf::Keyboard::Right)
	{
		if (field.CanMoveRight(*tetrimino))
		{
			tetrimino->MoveRight();
			gameData->assets.GetSound(FALL_SOUND).play();
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
		gameData->assets.GetSound(FALL_SOUND).play();
	}
	else
	{
		if (tetrimino->GetRow() == Tetrimino::StartingRow)
		{
			sf::Sound sound;
			sound = gameData->assets.GetSound(GAMEOVER_SOUND);
			sound.play();
			bool playing = true;
			while (playing)
			{
				auto status = sound.getStatus();
				switch (status)
				{
				case sf::Sound::Playing:
					Draw();
					break;
				default:
					playing = false;
					break;
				}
			}
			gameData->machine.AddState(std::make_unique<GameOverState>(gameData, currentScore));
		}
		field.ClearFieldAndSaveLastPosition();
		field.PlaceLastPositionOnField(tetrimino->GetColor());
		if (field.FindFullRows())
		{
			field.UpdatePoints(currentScore, linesCleared, level);
			fallingSpeed = startSpeed - (0.03f * level);
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
	scoreTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(currentScore);
	scoreTxtBox.SetContent(text, Alignment::CENTER);
	scoreTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, 25 });
	scoreTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	scoreTxtBox.CenterTopText();
	scoreTxtBox.CenterText();

	nextTxtBox.SetFont(font, charSize);
	text = "NEXT";
	nextTxtBox.SetContent(text, Alignment::TOP);
	float yPos = scoreTxtBox.GetPosition().y + scoreTxtBox.GetRect().height + TextBox::Margin;
	nextTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos});
	nextTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	nextTxtBox.CenterTopText();

	linesClearedTxtBox .SetFont(font, charSize);
	text = "LINES CLEARED";
	linesClearedTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(linesCleared);
	linesClearedTxtBox.SetContent(text, Alignment::CENTER);
	yPos = nextTxtBox.GetPosition().y + nextTxtBox.GetRect().height + TextBox::Margin;
	linesClearedTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos});
	linesClearedTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	linesClearedTxtBox.CenterTopText();
	linesClearedTxtBox.CenterText();

	droughtTxtBox.SetFont(font, charSize);
	text = "DROUGHT";
	droughtTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(droughtCount);
	droughtTxtBox.SetContent(text, Alignment::CENTER);
	yPos = linesClearedTxtBox.GetPosition().y + linesClearedTxtBox.GetRect().height + TextBox::Margin;
	droughtTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos});
	droughtTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	droughtTxtBox.CenterTopText();
	droughtTxtBox.CenterText();

	levelTxtBox.SetFont(font, charSize);
	text = "LEVEL";
	levelTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(level);
	levelTxtBox.SetContent(text, Alignment::CENTER);
	yPos = droughtTxtBox.GetPosition().y + droughtTxtBox.GetRect().height + TextBox::Margin;
	levelTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, yPos});
	levelTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	levelTxtBox.CenterTopText();
	levelTxtBox.CenterText();
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
	//gameData->machine.AddState(std::make_unique<GameOverState>(gameData, 40), false);
}
