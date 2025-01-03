#pragma once
#include <SFML/Graphics.hpp>

class Buff
{
public:
    Buff(sf::Texture* texture, sf::Vector2f position, int type);
    sf::Sprite spriteBuff;
    void draw(sf::RenderWindow* window);
    void getPosition() { return getPosition(); }
    void setPosition(sf::Vector2f position);
    void updateAnimation(float deltaTime);
    ~Buff();
    int getBuffType() {return type;}
    sf::Vector2f positionXY;
    int type = 0;
    int frameWidth = 64;
    int frameHeight = 64;
    int totalFrames = 4;
    int currentFrame = 0;
    float animationSpeed = 0.2f;
    float elapsedTime = 0.0f;
};

