#include "HighScores.h"

void HighScores::Load()
{
	highScores = FileHandler::ReadHighScoreFromFile();
}

void HighScores::SetNew(const size_t newScore)
{
	size_t index = 0;
	for (auto& score : highScores)
	{
		if (newScore > score.second)
		{
			break;
		}
		index++;
	}
	if (index < maxHighScoresSize)
	{
		scoreSet = true;
		isNewScore = true;
		auto it = highScores.begin() + index;
		highScores.insert(it, { "_  ", newScore });
		newScoreIndex = index;
	}
}

void HighScores::SetupTop10List(const sf::Font& font)
{
	sf::Text text;
	text.setFont(font);
	text.setFillColor(RED);
	size_t max = 0;
	for (auto& score : highScores)
	{
		std::string number = std::to_string(score.second);
		max = max < number.size() ? number.size() : max;
		std::string spacer = "";
		size_t diff = max - number.size();
		while (spacer.size() <= diff)
		{
			spacer.push_back(' ');
		}
		std::string setString = score.first + "                " + spacer + number;
		text.setString(setString);
		highScoreTexts.push_back(text);
	}
	top10Text.setFont(font);
	top10Text.setFillColor(RED);
	top10Text.setString("Top 10");
}

void HighScores::AddCharToScoreHolder(const size_t keyCode)
{
	std::string scoreTxtString = highScoreTexts[newScoreIndex].getString();
	if (scoreHolder.size() < 3 && keyCode >= 0 && keyCode < 27)
	{
		scoreHolder.push_back(letters[keyCode]);
		for (size_t i = 0; i < scoreHolder.size(); i++)
		{
			scoreTxtString[i] = scoreHolder[i];
		}
		if (scoreHolder.size() < 3)
		{
			scoreTxtString[scoreHolder.size()] = '_';
		}
		highScoreTexts[newScoreIndex].setString(scoreTxtString);
	}
}

void HighScores::RemoveCharFromScoreHolder()
{
	std::string scoreTxtString = highScoreTexts[newScoreIndex].getString();
	if (scoreHolder.size() != 0)
	{
		scoreHolder.pop_back();
		if (scoreHolder.size() < 3)
		{
			scoreTxtString[scoreHolder.size()] = '_';
			scoreTxtString[scoreHolder.size() + 1] = ' ';
		}
		highScoreTexts[newScoreIndex].setString(scoreTxtString);
	}
}

void HighScores::SaveScoreHolder()
{
	isNewScoreSet = true;
	highScores[newScoreIndex].first = scoreHolder;
	FileHandler::WriteHighScoresToFile(highScores);
	isNewScore = false;
}

bool HighScores::IsNewScore() const
{
	return isNewScore;
}

bool HighScores::IsNewScoreSet() const
{
	return isNewScoreSet;
}

const float HighScores::GetTopYPosition() const
{
	return top10Text.getPosition().y;
}

const float HighScores::GetBottomYPosition() const
{
	return highScoreTexts.back().getPosition().y + highScoreTexts.back().getLocalBounds().height;
}

void HighScores::Flash(const float dt)
{
	lastFlash += dt;
	if (isNewScore && (lastFlash > flashTime))
	{
		lastFlash = 0;
		if (!isNewScoreSet && switchColor)
		{
			highScoreTexts[newScoreIndex].setFillColor(TRANSPARENT);
		}
		else
		{
			highScoreTexts[newScoreIndex].setFillColor(RED);
		}
		switchColor = !switchColor;
	}
}

void HighScores::SetGuiElementPositions()
{
	float yStartPosition = WINDOW_HEIGHT / 7;
	float padding = 20.f;
	float width = top10Text.getGlobalBounds().width;
	top10Text.setPosition((WINDOW_WIDTH - width) / 2, yStartPosition);
	yStartPosition = yStartPosition + top10Text.getCharacterSize() + padding;
	float xStartPosition = highScoreTexts.size() > 0 ? (WINDOW_WIDTH - highScoreTexts[0].getLocalBounds().width) / 2 : 0;
	for (size_t i = 0; i < highScoreTexts.size(); i++)
	{
		float yNextPosition = (i * highScoreTexts[i].getCharacterSize()) + padding * (i + 1);
		highScoreTexts[i].setPosition(xStartPosition, yStartPosition + yNextPosition);
	}
}

void HighScores::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(top10Text);
	for (auto text : highScoreTexts)
	{
		wnd.draw(text);
	}
}
