#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

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
	SetupTextBox();
}

void GameState::Init()
{
	tetrimino = factory.CreateTetrimino();
	droughtCount += tetrimino->IsI() ? -1 * droughtCount : 1;
	nextTetrimino = factory.CreateTetrimino();
	preview.SetNext(*nextTetrimino);
	preview.Center();
}

void GameState::HandleInput()
{
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
	else if (gameData->input.KeyHit(sf::Keyboard::Key::Left))
	{
		if (field.CanMoveLeft(*tetrimino))
		{
			tetrimino->MoveLeft();
		}
	}
	else if (gameData->input.KeyHit(sf::Keyboard::Key::Right))
	{
		if (field.CanMoveRight(*tetrimino))
		{
			tetrimino->MoveRight();
		}
	}
	else if (gameData->input.KeyHit(sf::Keyboard::Key::Down))
	{
		Update(fallingSpeed + 1);
	}
	else if (gameData->input.KeyHit(sf::Keyboard::Key::Escape))
	{
		std::vector<TextBox> textBoxes;
		textBoxes.push_back(scoreTxtBox);
		textBoxes.push_back(nextTxtBox);
		textBoxes.push_back(linesClearedTxtBox);
		textBoxes.push_back(droughtTxtBox);
		textBoxes.push_back(levelTxtBox);
		gameData->machine.AddState(std::make_unique<PauseState>(gameData, field, textBoxes, preview), false);
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
		moveTimePassed += dt;
		if (moveTimePassed > fallingSpeed)
		{
			moveTimePassed = 0;
			MoveTetriminoOrPlaceOnField();
		}
		field.ShowOnField(*tetrimino);
		if (field.FindFullRows())
		{
			field.UpdatePoints(currentScore, linesCleared, level);
			fallingSpeed = startSpeed - (0.03f * level);
			UpdateTextBox();
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
	}
	else
	{
		if (tetrimino->GetRow() == Tetrimino::StartingRow)
		{
			gameData->machine.AddState(std::make_unique<GameOverState>(gameData, currentScore));
		}
		field.ClearFieldAndSaveLastPosition();
		field.PlaceLastPositionOnField(tetrimino->GetColor());
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
		nextTetrimino = factory.CreateTetrimino();
		preview.SetNext(*nextTetrimino);
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
