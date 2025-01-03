#include "Menu.h"


Menu::Menu(sf::Texture* texture, sf::RenderWindow* window) {
	title.setTexture(*texture);
	title.setTextureRect(sf::IntRect(896, 0, 512, 256));
	title.setPosition((window->getSize().x / 2) - 512 / 2-5, (window->getSize().y / 2) - 256 / 2-170);

	button1.setTexture(*texture);
	button1.setTextureRect(sf::IntRect(0, 384, buttonSizeX, buttonSizeY));
	button1.setPosition((window->getSize().x/2)- buttonSizeX/2, (window->getSize().y/2) - buttonSizeY / 2+40);

	button2.setTexture(*texture);
	button2.setTextureRect(sf::IntRect(0, 768, buttonSizeX, buttonSizeY));
	button2.setPosition((window->getSize().x / 2) - buttonSizeX / 2, (window->getSize().y / 2) - buttonSizeY / 2+100+100);
}
void Menu::draw(sf::RenderWindow* window) {
	window->draw(title);
	window->draw(button1);
	window->draw(button2);
}


bool Menu::isStartButtonClicked(sf::RenderWindow* window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	return sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		button1.getGlobalBounds().contains(mousePosition.x,mousePosition.y);
}
bool Menu::isExitButtonClicked(sf::RenderWindow* window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	return sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		button2.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}



