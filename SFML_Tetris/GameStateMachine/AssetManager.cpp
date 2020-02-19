#include "AssetManager.h"

void AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture texture;
	if (texture.loadFromFile(fileName))
	{
		textures.insert({ name, texture });
	}
}

sf::Texture& AssetManager::GetTexture(std::string name)
{
	return textures.at(name);
}

void AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;
	if (font.loadFromFile(fileName))
	{
		fonts.insert({ name, font});
	}
}

sf::Font& AssetManager::GetFont(std::string name)
{
	return fonts.at(name);
}
