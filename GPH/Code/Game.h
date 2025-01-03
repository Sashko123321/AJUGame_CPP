#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <iostream>

#include "Player.h"
#include "Menu.h"
#include "Coin.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "Portal.h"
#include "Buff.h"
#include "FonMusic.h"

class Game {
public:
    Game(int mainWindowWidth, int mainWindowHeight, std::wstring mainWindowTitle);
    ~Game();

    void run();
    void loadTexture();
    void loadSound();
    void inputCommand();
    void updateGame();
    void renderFrame();
    void setDefaultSettings();
    void introGame();
    void resetGame();
    void mainLowMenu();
    void setDefaultValues();
    void victory();
    void defeat();

    
    bool isMenuOpen = false;
    bool flagMiniMap = true;
    bool prevMKeyPressed = false;
    bool currentMKeyPressed = false;
    bool coinCountBool = true;
    int flagMenu = 0;
    int coinCount = 0;
    int maxCoins = 0;
    int maxEnemy = 0;
    int pass = 0;
    int maxBuff = 0;
    bool activeBoss = false;
    float coinValueIncrement = 0;


    

    sf::Clock clock;
    float deltaTime;

    sf::RenderWindow mainWindow;
    sf::Image image;
    sf::Texture texture[1];
    sf::Sprite backgroundSprite;
    
    Player* mainPlayer;
    Menu* mainMenu;
    Map* mainMap;
    Camera* mainCamera;
    Camera* miniMainCamera;
    Portal* mainPortal;
    Enemy* mainBoss;
    FonMusic* fonGameMusic;

    sf::SoundBuffer soundBuffer[9];
    sf::Sound sounds[9];
    sf::Sound coinSound, buttonSound, buffSound, bossLevelSound, winSound, loseSound;

    sf::RectangleShape rectWrap, rectCoinValue, rectCoin;
    sf::Sprite intr;

    sf::Vector2f cameraCenter;
    std::string currentLevel = "level_1.txt";

    std::list<Coin*> coinArray;
    std::list<Coin*> delCoinArray;
    std::list<Enemy*> enemyArray;
    std::list<Enemy*> delEnemyArray;
    std::list<Buff*> buffArray;
    std::list<Buff*> delBuffArray;
    bool isGameOver = false;
    int remainingCoins = 0;
};
