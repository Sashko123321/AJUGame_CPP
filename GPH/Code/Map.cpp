#include "Map.h"

Map::Map(sf::Texture* textureArray, std::string mapFileName) : texture(textureArray) {
    loadMap(mapFileName);
}

Map::~Map() {
    if (mapArray != nullptr) {
        for (int i = 0; i < mapSize.y; ++i) {
            delete[] mapArray[i];
        }
        delete[] mapArray;
        mapArray = nullptr;
    }
}

void Map::initializeMapArray(sf::Vector2i SizeXY) {
    mapSize = { SizeXY.x, SizeXY.y };
    mapArray = new char* [mapSize.y];
    for (int i = 0; i < mapSize.y; ++i) {
        mapArray[i] = new char[mapSize.x];
    }
}

void Map::loadMap(std::string mapFileName) {
    std::ifstream fileIn;
    nameMap = mapFileName;
    fileIn.open("Resours/Maps/" + mapFileName);
    if (!fileIn.is_open()) {
        std::cout << "Error open" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(fileIn, line)) {
        height++;
        if (line.length() > width) {
            width = line.length();
        }
    }
    fileIn.close();
    fileIn.open("Resours/Maps/" + mapFileName);
    if (!fileIn.is_open()) {
        std::cout << "Error open" << std::endl;
        return;
    }
    
    if (mapArray != nullptr) {
        for (int i = 0; i < mapSize.y; ++i) {
            delete[] mapArray[i];
        }
        delete[] mapArray;
        mapArray = nullptr;
    }
    std::cout << width << " /" << height << std::endl;
    initializeMapArray(sf::Vector2i(width, height));

    for (int y = 0; y < mapSize.y; ++y) {
        if (std::getline(fileIn, line)) {
            for (int x = 0; x < mapSize.x; ++x) {
                if (x < line.size()) {
                    mapArray[y][x] = line[x];
                    std::cout << line[x];
                }
                else {
                    mapArray[y][x] = ' '; 
                }
            }
            std::cout << std::endl;
        }
    }

    fileIn.close();
    scenaSize.x = mapSize.x * mapTileSize.x;
    scenaSize.y = mapSize.y * mapTileSize.y;
}



void Map::draw(sf::RenderWindow* window) {
    mapSprite.setTexture(*texture);
    for (int y = 0; y < mapSize.y; ++y) {
        for (int x = 0; x < mapSize.x; ++x) {
            switch (mapArray[y][x]) {
            case '1': mapSprite.setTextureRect(sf::IntRect(256, 256, mapTileSize.x, mapTileSize.y)); break;
            case '2': mapSprite.setTextureRect(sf::IntRect(320, 256, mapTileSize.x, mapTileSize.y)); break;
            case '3': mapSprite.setTextureRect(sf::IntRect(320, 256, -mapTileSize.x, mapTileSize.y)); break;
            case '4': mapSprite.setTextureRect(sf::IntRect(256, 320, mapTileSize.x, mapTileSize.y)); break;
            case '5': mapSprite.setTextureRect(sf::IntRect(320, 320, -mapTileSize.x, mapTileSize.y)); break;
            case '6': mapSprite.setTextureRect(sf::IntRect(256, 320, mapTileSize.x, -mapTileSize.y)); break;
            case '7': mapSprite.setTextureRect(sf::IntRect(320 + 64, 256 + 64, -mapTileSize.x, -mapTileSize.y)); break;
            case '8': mapSprite.setTextureRect(sf::IntRect(256 + 64, 256 + 64, -mapTileSize.x, -mapTileSize.y)); break;
            case '9': mapSprite.setTextureRect(sf::IntRect(320 + 64, 320, mapTileSize.x, mapTileSize.y)); break;
            case '0': mapSprite.setTextureRect(sf::IntRect(320 + 128, 320, -mapTileSize.x, mapTileSize.y)); break;
            case 'd': mapSprite.setTextureRect(sf::IntRect(256, 256, mapTileSize.x, mapTileSize.y)); break;
            case 'w': mapSprite.setTextureRect(sf::IntRect(320 + 128, 320 + 64, -mapTileSize.x, -mapTileSize.y)); break;
            case 'p': mapSprite.setTextureRect(sf::IntRect(320 + 64, 320 + 64, mapTileSize.x, -mapTileSize.y)); break;
            case 'u': mapSprite.setTextureRect(sf::IntRect(384, 256, mapTileSize.x, mapTileSize.y)); break;
            case 'f': mapSprite.setTextureRect(sf::IntRect(320, 320, mapTileSize.x, mapTileSize.y)); break;
            default: continue;
            }
            mapSprite.setPosition(x * mapTileSize.x, y * mapTileSize.y);
            window->draw(mapSprite);
        }
    }
}
char Map::getTileAt(int x, int y) {
    if (x >= 0 && x < mapSize.x && y >= 0 && y < mapSize.y)
        return mapArray[y][x];
    return '\0';
}
