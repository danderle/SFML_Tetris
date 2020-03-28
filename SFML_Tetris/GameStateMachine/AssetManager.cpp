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

void AssetManager::LoadSound(std::string name, std::string fileName)
{
	sf::SoundBuffer buffer;
	if (buffer.loadFromFile(fileName))
	{
		soundbuffers.emplace(name, buffer);
		sf::Sound sound;
		sound.setBuffer(GetSoundBuffer(name));
		sounds.emplace(name, sound);
	}

}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string name)
{
	return soundbuffers.at(name);
}

sf::Sound& AssetManager::GetSound(std::string name)
{
	return sounds.at(name);
}

void AssetManager::PlaySound(const std::string name)
{
	sounds.at(name).play();
}

const bool AssetManager::SoundStillPlaying(const std::string name) const
{
	auto status = sounds.at(name).getStatus();
	return status == sf::Sound::Playing;
}

void AssetManager::SetSoundsVolume(const float volume)
{
	soundsOn = volume > 0;
	for (auto& sound : sounds)
	{
		sound.second.setVolume(volume);
	}
}

const bool AssetManager::SoundsOn() const
{
	return soundsOn;
}

void AssetManager::StartMusic(std::string fileName)
{
	if (music.openFromFile(fileName))
	{
		music.setLoop(true);
		music.play();
	}
}

void AssetManager::StopMusic()
{
	music.stop();
}

void AssetManager::SetMusicVolume(const float volume)
{
	musicOn = volume > 0;
	music.setVolume(volume);
}

const bool AssetManager::MusicOn() const
{
	return musicOn;
}
