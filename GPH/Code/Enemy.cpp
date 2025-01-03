
#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f position,sf::Vector2f scale, sf::SoundBuffer* soundBuffer, float speed)
    : positionXY(position), speed(speed), frameCount(4), currentFrame(0), frameDuration(200.0f), animationTime(0.0f), soundBuffer(*soundBuffer){
    spriteEnemy.setTexture(*texture);
    spriteEnemy.setTextureRect(sf::IntRect(256, 0, 64, 64));
    spriteEnemy.setScale(scale);

    spriteEnemy.setPosition(positionXY);
    spriteEnemy.setColor(sf::Color(255, 255, 255, 128));
    timer.restart();
}

void Enemy::updatePosition(Player* player, float deltaTime) {
    sf::Vector2f enemyPosition = spriteEnemy.getPosition();
    sf::Vector2f direction = player->getPosition() - enemyPosition;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    coinCount = player->getCoinCount();
    if (coinCount > 0) {
        if (distance >= 45) {
            direction /= distance;

            sf::Vector2f newPosition = enemyPosition + direction * speed * deltaTime * 400.0f;

            spriteEnemy.setPosition(newPosition);

            updateAnimation(direction, deltaTime);
        }
        else {
            spriteEnemy.setTextureRect(sf::IntRect(256, 0, 64, 64));

            if (timer.getElapsedTime().asSeconds() > 1.5f) {
                player->setCoinCount();
                timer.restart();
            }
        }
    }
    else if (coinCount == 0) {
        randomMove(spriteEnemy.getPosition(), deltaTime);
    }

    playSound();
}

void Enemy::playSound() {
    if (timer.getElapsedTime().asSeconds() > interval) {
        sound.setBuffer(soundBuffer);
        sound.setVolume(10);

        if (sound.getStatus() == sf::Sound::Playing) {
            sound.stop();
        }
        else {
            sound.play();
        }

        timer.restart();
        interval = 1 + rand() % 5;
    }
}

void Enemy::randomMove(sf::Vector2f enemyPos, float deltaTime) {
    if (timer.getElapsedTime().asSeconds() > 2.5f) {
        randDirection = sf::Vector2f((float)(rand() % 3 - 1), (float)(rand() % 3 - 1));
        timer.restart();
    }
    if (randDirection.x != 0 || randDirection.y != 0) {
        randDirection /= std::sqrt(randDirection.x * randDirection.x + randDirection.y * randDirection.y);
    }
    sf::Vector2f newPosition = enemyPos + randDirection * speed * deltaTime * 100.0f;
    spriteEnemy.setPosition(newPosition);
    updateAnimation(randDirection, deltaTime);
}

void Enemy::updateAnimation(sf::Vector2f direction, float deltaTime) {
    animationTime += deltaTime * 1000;
    if (animationTime >= frameDuration) {
        animationTime = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount;
        if (std::abs(direction.x) > std::abs(direction.y)) {
            if (direction.x > 0) {spriteEnemy.setTextureRect(sf::IntRect(currentFrame * 64+256, 128, 64, 64));}
            else {spriteEnemy.setTextureRect(sf::IntRect(currentFrame * 64+256, 64, 64, 64));}
        }
        else {
            if (direction.y > 0) {spriteEnemy.setTextureRect(sf::IntRect(currentFrame * 64+256, 0, 64, 64));}
            else {spriteEnemy.setTextureRect(sf::IntRect(currentFrame * 64 + 256, 192, 64, 64));}
        }
    }
}

void Enemy::draw(sf::RenderWindow* window) {
    window->draw(spriteEnemy);
}

