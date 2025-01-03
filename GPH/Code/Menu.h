#pragma once
#include <SFML/Graphics.hpp>

class Menu{
public:
	Menu(sf::Texture* texture, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	bool isStartButtonClicked(sf::RenderWindow* window);
	bool isExitButtonClicked(sf::RenderWindow* window);
	sf::Sprite title;
	sf::Sprite button1;
	sf::Sprite button2;

	float buttonSizeX = 256;
	float buttonSizeY = 128;
};


	