#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Map.h"
#include "Portal.h"
#include "Coin.h"
#include "Buff.h"

class Player {
public:
    Player(sf::Texture* texture, Map* map, Portal* portal, sf::Vector2f position, float speed);

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveDiagonal(sf::Vector2i posDiagonalXY);
    void Stand();
    void updateAnimation(float deltaTime, int direction);
    void updateDiagonalAnimation(float shiftPos);
    void setPosition(int X, int Y);
    sf::Vector2f getPosition();
    void loadNextLevel();
    void resetLevel();
    bool collidesWithMap(Map* map, sf::Vector2f shiftPositionXY);
    bool touchPortal(Portal* portal);
    bool getCoins(Coin* coin);
    bool getBuff(Buff* buff);
    void updateBuffEffect();
    void activateSpeed();
    void activateShield();
    void playSound(sf::SoundBuffer* soundBuffer);
    void draw(sf::RenderWindow* window);
    bool getWin();
    int getCoinCount();
    void setCoinCount();
    void getPassCoin(int coin);
    void resetCoinCount();
    sf::Sprite spritePlayer;
    sf::CircleShape shield;
    sf::Sound sound;
    
    Map* mainMap;
    Portal* mainPortal;
    Buff* mainBuff;

    float speed;
    sf::Vector2f positionXY;
    float frameDuration;
    float animationTime;
    int frameCount;
    int currentFrame;
    int currentLevel = 1;
    int coinCount = 0;
    int passCoin = 0;

    bool win = false;
    bool isSpeedBoosted = false;
    bool isShieldActive = false;

    std::string nextLevelFile;
    sf::Clock timer;


};
