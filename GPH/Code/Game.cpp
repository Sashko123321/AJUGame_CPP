#include "Game.h"

Game::Game(int mainWindowWidth, int mainWindowHeight, std::wstring mainWindowTitle)
    : mainPlayer(nullptr), mainMenu(nullptr), mainMap(nullptr), mainCamera(nullptr), mainBoss(nullptr), mainPortal(nullptr), fonGameMusic(nullptr){
    mainWindow.create(sf::VideoMode(mainWindowWidth, mainWindowHeight), mainWindowTitle);
    mainWindow.setFramerateLimit(60);
    srand(time(NULL));
    loadTexture();
    loadSound();
    clock.restart();
}

Game::~Game() {
    if (mainPlayer != nullptr) delete mainPlayer;
    if (mainMenu != nullptr) delete mainMenu;
    if (mainMap != nullptr) delete mainMap;
    if (mainPortal != nullptr) delete mainPortal;
    if (mainBoss != nullptr) delete mainBoss;
    for (auto coin : coinArray) delete coin;
    coinArray.clear();
    for (auto enemy : enemyArray) delete enemy;
    enemyArray.clear();
    for (auto buff : buffArray) delete buff;
    buffArray.clear();
}

void Game::loadTexture() {
    image.loadFromFile("Resours/Textures/Tileset/Tileset+.png"); texture[0].loadFromImage(image);
}

void Game::loadSound() {
    std::string soundArray[] = { "coin.mp3", "intro.mp3", "move.mp3", "zvuk11.mp3", "buff.mp3", "bossLevel.mp3" , "enemy.mp3","win.mp3","lose.mp3" };
    for (int i = 0; i < 9; i++)
        soundBuffer[i].loadFromFile("Resours/Sound/" + soundArray[i]);

}

void Game::setDefaultSettings() {

    sf::Image myIcon;
    myIcon.loadFromFile("Resours/Textures/game/Logo.png");
    mainWindow.setIcon(myIcon.getSize().x, myIcon.getSize().y, myIcon.getPixelsPtr());
    sf::Image myCursorImage;
    myCursorImage.loadFromFile("Resours/Textures/game/Cursor.png");
    myCursorImage.createMaskFromColor(sf::Color(255, 255, 255));

    sf::Cursor myCursor;
    sf::Vector2u cursorClickPosition(3, 2);
    myCursor.loadFromPixels(myCursorImage.getPixelsPtr(), myCursorImage.getSize(), cursorClickPosition);
    mainWindow.setMouseCursor(myCursor);
    miniMainCamera->view.setViewport(sf::FloatRect(0, 0.8, 0.2, 0.2));
}

void Game::setDefaultValues() {
    if (mainMap->getnameMap() == "level_1.txt") {
        maxCoins = 10;
        maxEnemy = 3;
        pass = 3;
        maxBuff = 0;
        activeBoss = false;
    }
    else if (mainMap->getnameMap() == "level_2.txt") {
        maxCoins = 15;
        maxEnemy = 7;
        pass = 7;
        maxBuff = 3;
        activeBoss = false;

    }
    else if (mainMap->getnameMap() == "level_3.txt") {
        maxCoins = 20;
        maxEnemy = 7;
        pass = 10;
        maxBuff = 8;
        activeBoss = true;
    }
    else {
        maxCoins = 0;
        maxEnemy = 0;
        pass = 0;
        maxBuff = 0;
        activeBoss = false;
    }
}

void Game::introGame() {
    float alpha = 0;
    bool fadeIn = true;
    intr.setTexture(texture[0]);
    intr.setTextureRect(sf::IntRect(896, 0, 512, 256));
    intr.setPosition((mainWindow.getSize().x / 2) - 512 / 2, (mainWindow.getSize().y / 2) - 256 / 2);
    intr.setColor(sf::Color(255, 255, 255, alpha));
    while (clock.getElapsedTime().asSeconds() < 5.f) {
        mainWindow.clear();
        mainWindow.draw(backgroundSprite);
        if (fadeIn) {
            alpha += 2;
            if (alpha >= 255) {alpha = 255;fadeIn = false;}}
        else {alpha -= 2;if (alpha <= 0) break;}
        intr.setColor(sf::Color(255, 255, 255, alpha));
        mainWindow.draw(intr);
        mainWindow.display();
    }
}

void Game::mainLowMenu() {
    sf::Event menuEvent;
    sf::RectangleShape menuRect(sf::Vector2f(384, 384));
    int currentItemMenu = 0;
    int maxCountItemMenu = 3;
    menuRect.setTexture(&texture[0]);
    menuRect.setTextureRect(sf::IntRect(1408, 0, 384, 384));
    menuRect.setScale(1.5f, 1.5f);
    menuRect.setPosition(sf::Vector2f(mainCamera->getView()->getCenter().x - 384 * 1.5/2, mainCamera->getView()->getCenter().y - 384 * 1.5 /2));
    menuRect.setFillColor(sf::Color(255, 255, 255, 100));

    sf::RectangleShape menuButton[3];
    for (int i = 0; i < 3; i++) {
        menuButton[i].setSize(sf::Vector2f(256, 128));
        menuButton[i].setTexture(&texture[0]);
        menuButton[i].setTextureRect(sf::IntRect(0, 512 + 128 * i, 256, 128));
        menuButton[i].setScale(1.f,0.8f);
        menuButton[i].setPosition(sf::Vector2f(menuRect.getPosition().x + 160, menuRect.getPosition().y + 110 + 120 * i));
    }
    while (isMenuOpen) {
        while (mainWindow.pollEvent(menuEvent)) {
            if (menuEvent.type == sf::Event::KeyPressed) {
                if (menuEvent.key.code == sf::Keyboard::Up) {
                    currentItemMenu = (currentItemMenu - 1 >= 0) ? currentItemMenu - 1 : maxCountItemMenu - 1;
                    buttonSound.setBuffer(soundBuffer[3]);
                    buttonSound.play();
                }
                if (menuEvent.key.code == sf::Keyboard::Down) {
                    currentItemMenu = (currentItemMenu + 1 < maxCountItemMenu) ? currentItemMenu + 1 : 0;
                    buttonSound.setBuffer(soundBuffer[3]);
                    buttonSound.play();
                }
                if (menuEvent.key.code == sf::Keyboard::Escape) {isMenuOpen = false; }
                if (menuEvent.key.code == sf::Keyboard::Enter)
                {
                    if (currentItemMenu == 0) {}
                    if (currentItemMenu == 1) {
                        mainPlayer->setPosition(64 + 20, 64 + 20);
                        for (auto coin : coinArray) delete coin;
                        coinArray.clear();
                        for (auto enemy : enemyArray) delete enemy;
                        enemyArray.clear();
                        for (auto buff : buffArray) delete buff;
                        buffArray.clear();
                        if (mainBoss != nullptr) {
                            delete mainBoss;
                            mainBoss = nullptr;
                        }
                        mainMap->loadMap(currentLevel);

                        resetGame();
                        mainPlayer->resetCoinCount();
                        coinValueIncrement = 0;
                        rectCoinValue.setSize(sf::Vector2f(coinValueIncrement, 25));
                    }
                    if (currentItemMenu == 2) {
                        mainPlayer->setPosition(64 + 20, 64 + 20);
                        for (auto coin : coinArray) delete coin;
                        coinArray.clear();
                        for (auto enemy : enemyArray) delete enemy;
                        enemyArray.clear();
                        for (auto buff : buffArray) delete buff;
                        buffArray.clear();
                        if (mainBoss != nullptr) {
                            delete mainBoss;
                            mainBoss = nullptr;
                        }

                        currentLevel = "level_1.txt";
                        mainMap->loadMap(currentLevel);
                        mainPlayer->resetLevel();
                        mainPortal->setPosition(sf::Vector2f(1856, 64));
                        flagMenu = 0;
                        resetGame();
                        mainPlayer->resetCoinCount();
                        coinValueIncrement = 0;
                        rectCoinValue.setSize(sf::Vector2f(coinValueIncrement, 25));
                    }
                    buttonSound.setBuffer(soundBuffer[3]);
                    buttonSound.play();
                    isMenuOpen = false; 

                }
            }
        }
        mainWindow.draw(menuRect);
        for (int i = 0; i < 3; i++) {
            if (currentItemMenu == i){
                menuButton[i].setFillColor(sf::Color(255, 255, 255, 155)); 
                menuButton[i].setTextureRect(sf::IntRect(256, 512 + 128 * i, 256, 128));
            }
            else {
                menuButton[i].setTextureRect(sf::IntRect(0, 512 + 128 * i, 256, 128));

                menuButton[i].setFillColor(sf::Color(255, 255, 255, 255)); 
            }
            mainWindow.draw(menuButton[i]);
        }
        mainWindow.display();
    }
}

void Game::victory() {
    mainWindow.setView(mainWindow.getDefaultView());
    sf::Vector2f sizeVictory = { 256, 128 };
    sf::RectangleShape rectVictory;
    rectVictory.setSize(sf::Vector2f(sizeVictory.x, sizeVictory.y));
    rectVictory.setTexture(&texture[0]);
    rectVictory.setTextureRect(sf::IntRect(0, 896, sizeVictory.x, sizeVictory.y));
    rectVictory.setScale(1.5f, 1.5f);
    rectVictory.setPosition(mainWindow.getSize().x/2- (sizeVictory.x*1.5f)/2, mainWindow.getSize().y / 2 - (sizeVictory.y * 1.5f) / 2);
    winSound.setBuffer(soundBuffer[7]);
    winSound.play();
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < 3.f) {
        mainWindow.clear();
        mainWindow.draw(backgroundSprite);
        mainWindow.draw(rectVictory);
        mainWindow.display();
    }
    std::cout << "victory" << std::endl;
}

void Game::defeat()
{


    mainWindow.setView(mainWindow.getDefaultView());
    sf::Vector2f sizeDefeat = { 256, 128 };
    sf::RectangleShape rectDefeat;
    rectDefeat.setSize(sf::Vector2f(sizeDefeat.x, sizeDefeat.y));
    rectDefeat.setTexture(&texture[0]);
    rectDefeat.setTextureRect(sf::IntRect(256, 896, sizeDefeat.x, sizeDefeat.y));
    rectDefeat.setScale(1.5f, 1.5f);
    rectDefeat.setPosition(mainWindow.getSize().x / 2 - (sizeDefeat.x * 1.5f) / 2, mainWindow.getSize().y / 2 - (sizeDefeat.y * 1.5f) / 2);
    loseSound.setBuffer(soundBuffer[8]);
    loseSound.play();
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < 3.f) {
        mainWindow.clear();
        mainWindow.draw(backgroundSprite);
        mainWindow.draw(rectDefeat);
        mainWindow.display();
    }
    std::cout << "Defeat" << std::endl;
}



void Game::inputCommand() {
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) mainWindow.close();

        if (flagMenu != 0 &&!isMenuOpen && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            isMenuOpen = true;
            mainLowMenu();
        }
        /*if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta < 0.f)
            mainCamera->setZoom(1.1f);
        if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta > 0.f)
            mainCamera->setZoom(0.9f);*/
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add) {
            fonGameMusic->setVolume(5);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract) {
            fonGameMusic->setVolume(-5);
        }
    }

    if (mainMenu) {
        if (mainMenu->isExitButtonClicked(&mainWindow)) {
            buttonSound.setBuffer(soundBuffer[3]);
            buttonSound.play();
            mainWindow.close();
        }

        if (mainMenu->isStartButtonClicked(&mainWindow)) {
            buttonSound.setBuffer(soundBuffer[3]);
            buttonSound.play();
            delete mainMenu;
            mainMenu = nullptr;
            flagMenu = 2;
        }
    }

    bool isMoving = false;
    sf::Vector2i direction(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y = 1;

    if (direction.x != 0 || direction.y != 0) {
        if (direction.x != 0 && direction.y != 0) {
            mainPlayer->moveDiagonal(direction);
        }
        else if (direction.x != 0) {
            direction.x == 1 ? mainPlayer->moveRight() : mainPlayer->moveLeft();
        }
        else {
            direction.y == -1 ? mainPlayer->moveUp() : mainPlayer->moveDown();
        }
        isMoving = true;
        mainPlayer->playSound(&soundBuffer[2]);
    }

    if (!isMoving) { mainPlayer->Stand(); }

    currentMKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
    if (currentMKeyPressed && !prevMKeyPressed){ 
        flagMiniMap = !flagMiniMap;
    }
    prevMKeyPressed = currentMKeyPressed;
}

void Game::resetGame() {
    isGameOver = false;
    setDefaultValues();
    mainPlayer->getPassCoin(pass);
    remainingCoins = maxCoins-pass;


    for (auto coin : coinArray) delete coin;
    coinArray.clear();
    for (int i = 0; i < maxCoins; ++i) {
        int x, y;
        do {
            x = 64 + (rand() % ((int)(mainMap->getScenaSize().x / 64 - 2)) * 64);
            y = 64 + (rand() % ((int)(mainMap->getScenaSize().y / 64 - 2)) * 64);
        } while (mainMap->getTileAt(x / 64, y / 64) != 'f');
        coinArray.push_back(new Coin(&texture[0], sf::Vector2f(x, y)));
    }
    if (activeBoss && mainBoss == nullptr) {
        int x, y;
        do {
            x = 64 + (rand() % ((int)(mainMap->getScenaSize().x / 64 - 2)) * 64);
            y = 64 + (rand() % ((int)(mainMap->getScenaSize().y / 64 - 2)) * 64);
        } while (mainMap->getTileAt(x / 64, y / 64) != 'f');
        mainBoss = new Enemy(&texture[0], sf::Vector2f(x, y), sf::Vector2f(3.f, 3.f), &soundBuffer[5], 0.6f);
    }
    for (auto buff : buffArray) {
        delete buff;}
    buffArray.clear();
    for (int i = 0; i < maxBuff; ++i) {
        int x, y;
        do {
            x = 64 + (rand() % ((int)(mainMap->getScenaSize().x / 64 - 2)) * 64);
            y = 64 + (rand() % ((int)(mainMap->getScenaSize().y / 64 - 2)) * 64);
        } while (mainMap->getTileAt(x / 64, y / 64) != 'f');
        buffArray.push_back(new Buff(&texture[0], sf::Vector2f(x, y), 1+rand()%2 ));
    }

    for (auto enemy : enemyArray) delete enemy;
    enemyArray.clear();
    for (int i = 0; i < maxEnemy; ++i) {
        int x, y;
        do {
            x = 64 + (rand() % ((int)(mainMap->getScenaSize().x / 64 - 2)) * 64);
            y = 64 + (rand() % ((int)(mainMap->getScenaSize().y / 64 - 2)) * 64);
        } while (mainMap->getTileAt(x / 64, y / 64) != 'f');
        enemyArray.push_back(new Enemy(&texture[0], sf::Vector2f(x, y), sf::Vector2f(1.f, 1.f), &soundBuffer[6], (float)(100 + (rand() % 200)) / 1000));
    }
}

void Game::updateGame() {
    mainCamera->setCenter(mainPlayer->spritePlayer.getPosition());
    mainWindow.setView(mainCamera->view);
    deltaTime = clock.restart().asSeconds();
    mainPortal->updateAnimation(deltaTime);
    if (mainMap->getnameMap() != currentLevel) {
        currentLevel = mainMap->getnameMap();
        if (mainPlayer->win) {
            for (auto coin : coinArray) delete coin;
            coinArray.clear();
            for (auto enemy : enemyArray) delete enemy;
            enemyArray.clear();
            for (auto buff : buffArray) delete buff;
            buffArray.clear();
            if (mainBoss != nullptr) {
                delete mainBoss;
                mainBoss = nullptr;
            }
            victory();
            flagMenu = 0;
        }
        resetGame();
        if (coinCountBool) {
            mainPlayer->resetCoinCount();
            coinValueIncrement = 0;
            rectCoinValue.setSize(sf::Vector2f(coinValueIncrement, 25));
        }
        coinCountBool = false;
    }

    for (auto indexCoin : coinArray) {
        indexCoin->updateAnimation(deltaTime);
        if (mainPlayer->getCoins(indexCoin)) {
            coinSound.setBuffer(soundBuffer[0]);
            coinSound.play();
            std::cout << " >>> Coin collected" << std::endl;
            coinValueIncrement += (144.f / pass);
            remainingCoins--;
            delCoinArray.push_back(indexCoin);
        }
    }
    if (!delCoinArray.empty()) {
        for (auto indexDelCoin : delCoinArray) {
            delete indexDelCoin;
            coinArray.remove(indexDelCoin);
        }
    }
    if (mainPlayer->getCoinCount() <= pass) {
        coinValueIncrement = (mainPlayer->getCoinCount() / (float)pass) * 144.f;
        rectCoinValue.setSize(sf::Vector2f(coinValueIncrement, 25));
    }
    


    delCoinArray.clear();
    for (auto indexBuff : buffArray) {
        indexBuff->updateAnimation(deltaTime);
        if (mainPlayer->getBuff(indexBuff)) {
            buffSound.setBuffer(soundBuffer[4]);
            buffSound.play();
            std::cout << " >>> Buff collected" << std::endl;
            delBuffArray.push_back(indexBuff);
        }
    }
    mainPlayer->updateBuffEffect();
    if (!delBuffArray.empty()) {
        for (auto indexDelBuff : delBuffArray) {
            delete indexDelBuff;
            buffArray.remove(indexDelBuff);
        }
    }

    delBuffArray.clear();
    std::cout << " >>> isGameOver: " << isGameOver <<" / " << remainingCoins << " / " << coinValueIncrement << " / " << std::endl;
    if (!isGameOver && remainingCoins <= 0 && coinValueIncrement <= 0) {
        mainPlayer->setPosition(64 + 20, 64 + 20);
        for (auto coin : coinArray) delete coin;
        coinArray.clear();
        for (auto enemy : enemyArray) delete enemy;
        enemyArray.clear();
        for (auto buff : buffArray) delete buff;
        buffArray.clear();
        if (mainBoss != nullptr) {
            delete mainBoss;
            mainBoss = nullptr;
        }

        currentLevel = "level_1.txt";
        mainMap->loadMap(currentLevel);
        mainPlayer->resetLevel();
        mainPortal->setPosition(sf::Vector2f(1856, 64));
        defeat();
        isGameOver = true;
        flagMenu = 0;
        resetGame();
        mainPlayer->resetCoinCount();
        coinValueIncrement = 0;
        rectCoinValue.setSize(sf::Vector2f(coinValueIncrement, 25));
    }
}

void Game::renderFrame() {
    mainWindow.clear();
    if (flagMenu == 0) {
        std::cout << " >>> mainMenu draw" << std::endl;

        mainWindow.setView(mainWindow.getDefaultView());
        mainWindow.draw(backgroundSprite);
        
        if (mainMenu == nullptr){
            mainMenu = new Menu(&texture[0], &mainWindow);
        }
        mainMenu->draw(&mainWindow);

    }
    else if (flagMenu == 2) {

        mainMap->draw(&mainWindow);
        
        mainPortal->draw(&mainWindow);
        for (auto indexCoin : coinArray) {
            indexCoin->draw(&mainWindow);
        }
        for (auto indexBuff : buffArray) {
            indexBuff->draw(&mainWindow);
        }

        mainPlayer->draw(&mainWindow);

        if (mainBoss != nullptr) {
            mainBoss->draw(&mainWindow);
            mainBoss->updatePosition(mainPlayer, deltaTime);
        }
        for (auto indexEnemy : enemyArray) {
            indexEnemy->draw(&mainWindow);
            indexEnemy->updatePosition(mainPlayer, deltaTime);
        }
        
        sf::Vector2f cameraCenter(mainCamera->view.getCenter().x + mainCamera->view.getSize().x / 2 - 256, mainCamera->view.getCenter().y - mainCamera->view.getSize().y / 2 + 20);

        rectCoinValue.setFillColor(sf::Color::Yellow);
        rectCoinValue.setPosition(sf::Vector2f(cameraCenter.x + 75, cameraCenter.y + 20));
        mainWindow.draw(rectCoinValue);

        rectWrap.setSize(sf::Vector2f(256, 64));
        rectWrap.setTexture(&texture[0]);
        rectWrap.setTextureRect(sf::IntRect(448, 320, 256, 64));
        rectWrap.setPosition(cameraCenter);
        mainWindow.draw(rectWrap);

        rectCoin.setSize(sf::Vector2f(64, 64));
        rectCoin.setTexture(&texture[0]);
        rectCoin.setTextureRect(sf::IntRect(448, 256, 64, 64));
        rectCoin.setScale(0.5f, 0.5f);
        rectCoin.setPosition(sf::Vector2f(cameraCenter.x + 30, cameraCenter.y + 16));
        mainWindow.draw(rectCoin);

        if (flagMiniMap) {
            mainWindow.setView(miniMainCamera->view);
            mainMap->draw(&mainWindow);
            mainPortal->draw(&mainWindow);
            for (auto indexCoin : coinArray) {
                indexCoin->draw(&mainWindow);
            }
            for (auto indexBuff : buffArray) {
                indexBuff->draw(&mainWindow);
            }
            for (auto indexEnemy : enemyArray) {
                indexEnemy->draw(&mainWindow);
            }
            if (mainBoss != nullptr) {
                mainBoss->draw(&mainWindow);
            }


            mainPlayer->draw(&mainWindow);
            mainWindow.setView(mainCamera->view);

        }
        
    }
    mainWindow.display();
}


void Game::run() {
    //=============+ BG +==============
    backgroundSprite.setTexture(texture[0]);
    backgroundSprite.setTextureRect(sf::IntRect(512,384,960,640));
    backgroundSprite.setColor(sf::Color(255, 255, 255, 100));
    backgroundSprite.setScale(1.1f, 1.1f);
    //=============+ BG +==============
    
    mainMenu = new Menu(&texture[0], &mainWindow);
    mainMap = new Map(&texture[0], currentLevel);
    mainPortal = new Portal(&texture[0], sf::Vector2f(1856, 64));
    mainPlayer = new Player(&texture[0], mainMap, mainPortal, sf::Vector2f(64 + 20, 64 + 20), 0.3f);

    resetGame();

    //=============+ Music +==============
    fonGameMusic = new FonMusic("retro-game-music.mp3");
    fonGameMusic->fonMusic.setVolume(10);
    //=============+ Music +==============

    mainCamera = new Camera(mainMap->getScenaSize() * .5f, mainMap->getScenaSize());
    miniMainCamera = new Camera(mainMap->getScenaSize(), mainMap->getScenaSize());

    setDefaultSettings();
    introGame();
    while (mainWindow.isOpen()) {
        inputCommand();
        updateGame();
        renderFrame();
    }
}
