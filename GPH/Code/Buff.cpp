#include "Buff.h"

Buff::Buff(sf::Texture* texture, sf::Vector2f position, int type) : positionXY(position), type(type){
    // 1 - speed
    // 2 - protect
    spriteBuff.setTexture(*texture);
    if (type == 1)
    {
        spriteBuff.setTextureRect(sf::IntRect(512, 192, frameWidth, frameHeight));
    }
    if (type == 2)
    {
        spriteBuff.setTextureRect(sf::IntRect(512, 128, frameWidth, frameHeight));
    }
    spriteBuff.setScale(0.7f, 0.7f);
    spriteBuff.setPosition(position);

}
Buff::~Buff() {};
void Buff::draw(sf::RenderWindow* window) {
    window->draw(spriteBuff);
}

void Buff::setPosition(sf::Vector2f position) {
    spriteBuff.setPosition(position);
}
void Buff::updateAnimation(float deltaTime) {
    elapsedTime += deltaTime;
    if (type == 1)
    {
        if (elapsedTime >= animationSpeed) {
            elapsedTime = 0.0f;
            currentFrame = (currentFrame + 1) % totalFrames;
            spriteBuff.setTextureRect(sf::IntRect(512 + currentFrame * frameWidth, 192, frameWidth, frameHeight));
        }
    }
    if (type == 2)
    {
        if (elapsedTime >= animationSpeed) {
            elapsedTime = 0.0f;
            currentFrame = (currentFrame + 1) % totalFrames;
            spriteBuff.setTextureRect(sf::IntRect(512 + currentFrame * frameWidth, 128, frameWidth, frameHeight));
        }
        
    }
    
}


