#include "Coin.h"

Coin::Coin(sf::Texture* texture, sf::Vector2f position) : positionXY(position) {
	spriteCoin.setTexture(*texture);
	spriteCoin.setTextureRect(sf::IntRect(384+64, 256, frameWidth, frameHeight));
	spriteCoin.setScale(0.5f, 0.5f);
	spriteCoin.setPosition(position);
}
Coin::~Coin() {};
void Coin::draw(sf::RenderWindow* window) {
	window->draw(spriteCoin);
}

void Coin::remove() {
	collected = true; 
}
sf::Vector2f Coin::getPosition() {
	return spriteCoin.getPosition();
}
void Coin::updateAnimation(float deltaTime) {
	elapsedTime += deltaTime;
	if (elapsedTime >= animationSpeed) {
		elapsedTime = 0.0f;
		currentFrame = (currentFrame + 1) % totalFrames;
		spriteCoin.setTextureRect(sf::IntRect(384+64 + currentFrame * frameWidth, 256, frameWidth, frameHeight));

	}
}
void Coin::playSound(sf::SoundBuffer* soundBuffer) {
		sound.setBuffer(*soundBuffer);
		sound.setVolume(100);
		sound.play();
}
