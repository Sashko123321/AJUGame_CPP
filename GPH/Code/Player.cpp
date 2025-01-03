#include "Player.h"
#include <iostream>


Player::Player(sf::Texture* texture, Map* map, Portal* portal, sf::Vector2f position, float speed)
    : positionXY(position), speed(speed), mainMap(map), mainPortal(portal),
    frameCount(4), currentFrame(0), frameDuration(500.0f), animationTime(0.0f) {
    spritePlayer.setTexture(*texture);
    spritePlayer.setTextureRect(sf::IntRect(0, 0, 64, 64));
    spritePlayer.setPosition(positionXY);
    shield.setRadius(40);
    shield.setFillColor(sf::Color(0, 0, 255, 100));
    shield.setOrigin(shield.getRadius(), shield.getRadius());
}

bool Player::collidesWithMap(Map* map, sf::Vector2f shiftPostitionXY) {
   
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int tileX = (positionXY.x + shiftPostitionXY.x + i * spritePlayer.getGlobalBounds().width) / map->getMapTileSize().x;
            int tileY = (positionXY.y + shiftPostitionXY.y + j * spritePlayer.getGlobalBounds().height) / map->getMapTileSize().y;

            if (tileX >= 0 && tileX < map->getMapSize().x && tileY >= 0 && tileY < map->getMapSize().y) {
                if (map->getMapArray()[tileY][tileX] != 'f')
                    return true;
            }
        }
    }
    return false;
}
void Player::draw(sf::RenderWindow* window) {
    window->draw(spritePlayer);
    if (isShieldActive) {
        shield.setPosition(spritePlayer.getPosition().x + 32, spritePlayer.getPosition().y + 32);
        window->draw(shield);
    }
}


//==========Move=============
void Player::moveRight() {
    if (!collidesWithMap(mainMap, sf::Vector2f(speed * 10, 0))) {
        positionXY.x += speed * 10;
        spritePlayer.setPosition(positionXY);
    }
    updateAnimation(0.1f, 2);
    if (touchPortal(mainPortal) && coinCount >= passCoin) {
        loadNextLevel();
    }
}
void Player::moveLeft() {
    if (!collidesWithMap(mainMap, sf::Vector2f(-speed * 10, 0))) {
        positionXY.x -= speed * 10;
        spritePlayer.setPosition(positionXY);
    }
    updateAnimation(0.1f, 1);
    if (touchPortal(mainPortal) && coinCount >= passCoin) {
        loadNextLevel();
    }
}
void Player::moveUp() {
    if (!collidesWithMap(mainMap, sf::Vector2f(0, -speed * 10))) {
        positionXY.y -= speed * 10;
        spritePlayer.setPosition(positionXY);
    }
    updateAnimation(0.1f, 3);
    if (touchPortal(mainPortal) && coinCount >= passCoin) {
        loadNextLevel();
    }
}
void Player::moveDown() {
    if (!collidesWithMap(mainMap, sf::Vector2f(0, speed * 10))) {
        positionXY.y += speed * 10;
        spritePlayer.setPosition(positionXY);
    }
    updateAnimation(0.1f, 0);
    if (touchPortal(mainPortal) && coinCount >= passCoin) {
        loadNextLevel();
    }
}
void Player::Stand() {spritePlayer.setTextureRect(sf::IntRect(0, 0, 64, 64));}
void Player::moveDiagonal(sf::Vector2i posDiagonalXY) {

    if (!collidesWithMap(mainMap, sf::Vector2f(posDiagonalXY.x * speed * 8, posDiagonalXY.y * speed * 8))) {
        positionXY.x = positionXY.x + posDiagonalXY.x * speed * 8;
        positionXY.y = positionXY.y + posDiagonalXY.y * speed * 8;;
        spritePlayer.setPosition(positionXY);
    }
    updateDiagonalAnimation(posDiagonalXY.y);
}
//==========Move=============

//==========Animation=============
void Player::updateDiagonalAnimation(float offsetY) {
    int direction;
    if (offsetY < 0) {direction = 3;}
    else {direction = 0;}
    updateAnimation(0.1f, direction);
}

void Player::updateAnimation(float deltaTime, int direction) {
    animationTime += deltaTime * 1000;
    if (animationTime >= frameDuration) {
        animationTime = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount;
        spritePlayer.setTextureRect(sf::IntRect(currentFrame * 64, direction * 64, 64, 64));}
}
//==========Animation=============

//==========Effects=============
void Player::updateBuffEffect() {
    if (isSpeedBoosted && timer.getElapsedTime().asMilliseconds() >= 3000) {
        speed = 0.3f;
        isSpeedBoosted = false;
    }
    if (isShieldActive && timer.getElapsedTime().asMilliseconds() >= 5000) {
        isShieldActive = false;
    }
}
bool Player::getCoins(Coin* coin) {
    if (spritePlayer.getGlobalBounds().intersects(coin->spriteCoin.getGlobalBounds()) == true) {
        coinCount++;
        return true;
    }
    return false;
}
bool Player::getBuff(Buff* buff) {
    if (spritePlayer.getGlobalBounds().intersects(buff->spriteBuff.getGlobalBounds())) {
        mainBuff = buff;
        if (mainBuff != nullptr) {
            if (mainBuff->getBuffType() == 1) {
                activateSpeed(); 
            }
            if (mainBuff->getBuffType() == 2) {
                activateShield(); 
            }
            return true;    
        }
    }
    return false;
}
//==========Effects=============




void Player::loadNextLevel() {
    win = false;
    currentLevel++;
    std::cout << win << std::endl;

    if (currentLevel == 2) {
        nextLevelFile = "level_2.txt";
        mainPortal->setPosition(sf::Vector2f(1856, 1152));}
    else if (currentLevel == 3) {
        nextLevelFile = "level_3.txt";
        mainPortal->setPosition(sf::Vector2f(1856, 1152)); }
    
    else {
        if (nextLevelFile == "level_3.txt" && spritePlayer.getGlobalBounds().intersects(mainPortal->spritePostal.getGlobalBounds())){win = true;}
        currentLevel = 1;
        nextLevelFile = "level_1.txt";
        mainPortal->setPosition(sf::Vector2f(1856, 64)); 
    }
    mainMap->loadMap(nextLevelFile);
    positionXY = sf::Vector2f(64 + 20, 64 + 20); 
    spritePlayer.setPosition(positionXY);
    resetCoinCount();
}

void Player::playSound(sf::SoundBuffer* soundBuffer) {
    if (sound.getStatus() != sf::Sound::Playing) {
        sound.setBuffer(*soundBuffer);
        sound.setVolume(90);
        sound.play();
    }
}

void Player::resetCoinCount() { coinCount = 0; }

void Player::getPassCoin(int coin) { passCoin = coin; }

void Player::resetLevel() {
    nextLevelFile = "level_1.txt";
    currentLevel = 1;
}
void Player::setPosition(int X, int Y) {
    positionXY.x = X;
    positionXY.y = Y;
    spritePlayer.setPosition(sf::Vector2f(X, Y));
}
int Player::getCoinCount() { return coinCount; }
void Player::setCoinCount() {
    if (isShieldActive) {}
    else { coinCount--; }
}
bool Player::getWin() { return win; }
void Player::activateSpeed() {
    speed = 0.9f;
    timer.restart();
    isSpeedBoosted = true;
}
void Player::activateShield() {
    isShieldActive = true;
    timer.restart();
}
sf::Vector2f Player::getPosition() { return spritePlayer.getPosition(); }

bool Player::touchPortal(Portal* portal) {
    if (spritePlayer.getGlobalBounds().intersects(portal->spritePostal.getGlobalBounds())) {
        return true;
    }
    return false;
}