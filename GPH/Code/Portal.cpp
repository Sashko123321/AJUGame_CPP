#include "Portal.h"

Portal::Portal(sf::Texture* texture, sf::Vector2f position) : positionXY(position) {
    spritePostal.setTexture(*texture);
    spritePostal.setTextureRect(sf::IntRect(512, 0, frameWidth, frameHeight));
    spritePostal.setScale(0.9f, 0.9f);
    spritePostal.setPosition(position);
}

Portal::~Portal() {};
void Portal::draw(sf::RenderWindow* window) {
    window->draw(spritePostal);
}
void Portal::setPosition(sf::Vector2f position){
    spritePostal.setPosition(position);
}
void Portal::updateAnimation(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= animationSpeed) {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
        spritePostal.setTextureRect(sf::IntRect(512 + currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
}