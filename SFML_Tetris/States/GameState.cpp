#include "GameState.h"

//// initialize TetriminoFactory one time
TetriminoFactory GameState::factory;

GameState::GameState(std::shared_ptr<GameData> _gameData)
	:
	gameData(_gameData),
	field({(float)Field::FrameThickness, gameData->window.getSize().y - (float)(Field::Height + Field::FrameThickness)}),
	scoreTxtBox( WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 3, BLACK),
	nextTxtBox(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 3, BLACK),
	linesCleared(WINDOW_WIDTH - Field::TotalWidth - TextBox::Margin, WINDOW_HEIGHT / 3, BLACK),
	preview(nextTxtBox)
{
	const auto& font = gameData->assets.GetFont(ROBOT_FONT);
	SetupScoreTextBox(font);
	SetupNextTextBox(font);
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
		preview.Center();
	}
}

void GameState::SetupScoreTextBox(const sf::Font& font)
{
	scoreTxtBox.SetFont(font);
	std::string text = "SCORE\n" + std::to_string(currentScore);
	scoreTxtBox.SetContent(text);
	scoreTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, 0 });
	scoreTxtBox.SetOutline(LIGHTGRAY, -18);
	scoreTxtBox.CenterText();
}

void GameState::SetupNextTextBox(const sf::Font& font)
{
	nextTxtBox.SetFont(font);
	std::string text = "NEXT";
	nextTxtBox.SetContent(text);
	nextTxtBox.SetPosition({ Field::TotalWidth + TextBox::Margin, scoreTxtBox.GetRect().height + TextBox::Margin});
	nextTxtBox.SetOutline(LIGHTGRAY, -18);
	nextTxtBox.CenterTopText();
}
