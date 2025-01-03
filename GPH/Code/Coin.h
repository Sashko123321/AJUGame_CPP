#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Coin{
public:
	Coin(sf::Texture* texture, sf::Vector2f position);
	void draw(sf::RenderWindow* window);
	sf::Sprite spriteCoin;
	sf::Vector2f positionXY;
	sf::Vector2f getPosition();
	~Coin();
	bool collected = false;
	void remove();
	int frameWidth = 64;
	int frameHeight = 64;
	int totalFrames = 6;
	int currentFrame = 0;
	float animationSpeed = 0.1f;
	float elapsedTime = 0.0f;
	void updateAnimation(float deltaTime);
	sf::Sound sound;
	void playSound(sf::SoundBuffer* soundBuffer);
};

