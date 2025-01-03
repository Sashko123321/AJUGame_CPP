#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <cmath>

class Enemy {
public:
    Enemy(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, sf::SoundBuffer* soundBuffer, float speed);
    void updatePosition(Player* player, float deltaTime);
    void draw(sf::RenderWindow* window);
    sf::Sprite spriteEnemy;
    sf::Vector2f positionXY;
    float speed;
    int frameCount;
    int currentFrame;
    float frameDuration;
    int coinCount;
    float animationTime;
    sf::Vector2f enemyPosition;
    sf::Clock timer;
    sf::Vector2f randDirection;
    float elapsedTime;
    void randomMove(sf::Vector2f enemyPos, float deltaTime);
    void updateAnimation(sf::Vector2f direction, float deltaTime);

    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    void playSound();

    bool isPlaying = false;
    float interval;
};
