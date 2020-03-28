#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager() = default;

	void LoadTexture(std::string name, std::string fileName);
	sf::Texture& GetTexture(std::string name);

	void LoadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);

	void LoadSound(std::string name, std::string fileName);
	sf::SoundBuffer& GetSoundBuffer(std::string name);
	sf::Sound& GetSound(std::string name);
	void PlaySound(const std::string name);
	const bool SoundStillPlaying(const std::string name) const;
	void SetSoundsVolume(const float volume);
	const bool SoundsOn() const;
	void StartMusic(std::string fileName);
	void StopMusic();
	void SetMusicVolume(const float volume);
	const bool MusicOn() const;

private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::SoundBuffer> soundbuffers;
	std::map<std::string, sf::Sound> sounds;
	sf::Music music;
	bool musicOn = true;
	bool soundsOn = true;
};

