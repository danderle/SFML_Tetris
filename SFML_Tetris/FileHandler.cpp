#include "FileHandler.h"

std::string FileHandler::highScoreFilePath = "";
std::string FileHandler::appDataTetrisDirectory = "";

void FileHandler::CreateAppDataDirectory()
{
	char* pValue;
	size_t len;
	if (_dupenv_s(&pValue, &len, "APPDATA") == 0)
	{
		std::stringstream ss;
		ss << pValue << "\\Tetris\\";
		appDataTetrisDirectory = ss.str();
		if (!std::filesystem::exists(appDataTetrisDirectory))
		{
			std::filesystem::create_directory(appDataTetrisDirectory);
		}
		highScoreFilePath = appDataTetrisDirectory + "HighScores.txt";
	}
	else
	{
		throw std::exception::exception("HighScore file creation failed");
	}
	free(pValue);
}

std::vector<std::pair<std::string, size_t>> FileHandler::ReadHighScoreFromFile()
{
	std::vector<std::pair<std::string, size_t>> highScores;
	std::ifstream inputStream(FileHandler::highScoreFilePath);
	std::string line;
	while (std::getline(inputStream, line).good() && !line.empty() && highScores.size() < 10)
	{
		std::stringstream ss;
		ss << line;
		std::string name;
		size_t score = 0;
		ss >> name;
		ss >> score;
		while (name.size() < 3)
		{
			name.push_back(' ');
		}
		highScores.emplace_back(name, score);
	}
	inputStream.close();
	return highScores;
}

void FileHandler::WriteHighScoresToFile(std::vector<std::pair<std::string, size_t>> highScores)
{
	std::ofstream outStream(FileHandler::highScoreFilePath);
	for (auto highScore : highScores)
	{
		highScore.first = highScore.first.empty() ? "XXX" : highScore.first;
		outStream << highScore.first << " " << std::to_string(highScore.second) << std::endl;
	}
	outStream.close();
}
