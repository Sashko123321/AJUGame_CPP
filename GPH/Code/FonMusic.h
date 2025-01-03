#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class FonMusic
{
public:
	sf::Music fonMusic;
	std::string fonMusicFileName;
	std::string fonMusicDirectoryPath = "Resours/Music/";
	FonMusic(std::string musicFileName);
	void setFonMusic(std::string musicFileName);
	void setVolume(int volume);
};

