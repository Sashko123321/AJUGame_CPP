#pragma once
#include <SFML/Graphics.hpp>

class Portal
{
public:
    Portal(sf::Texture* texture, sf::Vector2f position);
    void draw(sf::RenderWindow* window);
    sf::Vector2f positionXY;
    sf::Sprite spritePostal;
    void getPosition() { return getPosition(); }
    void setPosition(sf::Vector2f position);
    ~Portal();
    int frameWidth = 64;
    int frameHeight = 128;
    int totalFrames = 6;
    int currentFrame = 0;
    float animationSpeed = 0.1f;
    float elapsedTime = 0.0f;
    void updateAnimation(float deltaTime);
};
