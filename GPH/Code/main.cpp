#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main() {
	Game myGame(960, 600, L"A.J.U.");
	myGame.run();
}
