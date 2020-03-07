#include "GameState.h"

//// initialize TetriminoFactory one time
TetriminoFactory GameState::factory;

GameState::GameState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	field({(float)Field::FrameThickness, gameData->window.getSize().y - (float)(Field::Height + Field::FrameThickness)}),
	scoreTxtBox( WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 5, BLACK),
	nextTxtBox(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 4, BLACK),
	linesClearedTxtBox(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 5, BLACK),
	preview(nextTxtBox)
{
	SetupTextBox();
}

void GameState::Init()
{
	tetrimino = factory.CreateTetrimino();
	nextTetrimino = factory.CreateTetrimino();
	preview.SetNext(*nextTetrimino);
	preview.Center();
}

void GameState::HandleInput()
{
	if (manualTimePassed > manualMoveTime)
	{
		if (gameData->input.KeyHit(sf::Keyboard::Key::Left))
		{
			manualTimePassed = 0;
			if (field.CanMoveLeft(*tetrimino))
			{
				tetrimino->MoveLeft();
			}
		}
		if (gameData->input.KeyHit(sf::Keyboard::Key::Right))
		{
			manualTimePassed = 0;
			if (field.CanMoveRight(*tetrimino))
			{
				tetrimino->MoveRight();
			}
		}
		if (gameData->input.KeyHit(sf::Keyboard::Key::Down))
		{
			manualTimePassed = 0;
			autoTimePassed = 0;
			MoveTetriminoOrPlaceOnField();
		}
	}
}

void GameState::HandleInput(sf::Event event)
{
	if (event.key.code == sf::Keyboard::A)
	{
		tetrimino->RotateLeft();
		if (!field.CanRotate(*tetrimino))
		{
			tetrimino->RotateRight();
		}
	}
	else if (event.key.code == sf::Keyboard::D)
	{
		tetrimino->RotateRight();
		if (!field.CanRotate(*tetrimino))
		{
			tetrimino->RotateLeft();
		}
	}
}

void GameState::Update(float dt)
{
	manualTimePassed += dt;
	autoTimePassed += dt;
	if (autoTimePassed > autoMoveTime)
	{
		autoTimePassed = 0;
		MoveTetriminoOrPlaceOnField();
	}
	field.ShowOnField(*tetrimino);
	field.ClearFullRows();
}

void GameState::Draw()
{
	gameData->window.clear();
	field.Draw(gameData->window);
	scoreTxtBox.Draw(gameData->window);
	nextTxtBox.Draw(gameData->window);
	linesClearedTxtBox.Draw(gameData->window);
	preview.Draw(gameData->window);
	gameData->window.display();
}


//// **** Private Functions ****

void GameState::MoveTetriminoOrPlaceOnField()
{
	if (field.CanMoveDown(*tetrimino))
	{
		tetrimino->MoveDown();
	}
	else
	{
		field.ClearFieldAndSaveLastPosition();
		field.PlaceLastPositionOnField(tetrimino->GetColor());
		tetrimino = std::move(nextTetrimino);
		nextTetrimino = factory.CreateTetrimino();
		preview.SetNext(*nextTetrimino);
	}
}

void GameState::SetupTextBox()
{
	const auto& font = gameData->assets.GetFont(ROBOT_FONT);
	float outlineThickness = -15;
	unsigned int charSize = 20;
	scoreTxtBox.SetFont(font, charSize);
	std::string text = "SCORE";
	scoreTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(currentScore);
	scoreTxtBox.SetContent(text, Alignment::CENTER);
	scoreTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, 0 });
	scoreTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	scoreTxtBox.CenterTopText();
	scoreTxtBox.CenterText();

	nextTxtBox.SetFont(font, charSize);
	text = "NEXT";
	nextTxtBox.SetContent(text, Alignment::TOP);
	nextTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, scoreTxtBox.GetRect().height + TextBox::Margin });
	nextTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	nextTxtBox.CenterTopText();

	linesClearedTxtBox .SetFont(font, charSize);
	text = "LINES CLEARED";
	linesClearedTxtBox.SetContent(text, Alignment::TOP);
	text = std::to_string(linesCleared);
	linesClearedTxtBox.SetContent(text, Alignment::CENTER);
	linesClearedTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, scoreTxtBox.GetRect().height + nextTxtBox.GetRect().height + TextBox::Margin * 2 });
	linesClearedTxtBox.SetOutline(LIGHTGRAY, outlineThickness);
	linesClearedTxtBox.CenterTopText();
	linesClearedTxtBox.CenterText();
}