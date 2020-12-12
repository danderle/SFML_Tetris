#pragma once
#include "DEFINITIONS.h"
#include <filesystem>
#include <vector>
#include <sstream>
#include <fstream>

class FileHandler
{
public:
	FileHandler() = default;

	static void CreateAppDataDirectory();
	static std::vector<std::pair<std::string, size_t>> ReadHighScoreFromFile();
	static void WriteHighScoresToFile(std::vector<std::pair<std::string, size_t>> highScores);
	static std::string highScoreFilePath;
	static std::string appDataTetrisDirectory;
};

