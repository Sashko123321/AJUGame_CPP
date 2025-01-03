#include "FonMusic.h"


FonMusic::FonMusic(std::string musicFileName):fonMusicFileName(musicFileName){
	fonMusic.openFromFile(fonMusicDirectoryPath + fonMusicFileName);
	fonMusic.play();

}

void FonMusic::setFonMusic(std::string musicFileName)
{
	fonMusicFileName = musicFileName;
	fonMusic.stop();

	fonMusic.openFromFile(fonMusicDirectoryPath + fonMusicFileName);
	fonMusic.play();

}

void FonMusic::setVolume(int volume)
{
	if (volume < 0) {
		if (fonMusic.getVolume() + volume >= 0)
			fonMusic.setVolume(fonMusic.getVolume() + volume);
		else 
			fonMusic.setVolume(0);
	}
	if (volume > 0) {
		if (fonMusic.getVolume() + volume <= 100)
			fonMusic.setVolume(fonMusic.getVolume() + volume);
		else
			fonMusic.setVolume(100);
	}
}
