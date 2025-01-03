#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>

class Map {
public:
    Map(sf::Texture* textureArray, std::string mapFileName);
    ~Map();

    char getTileAt(int x, int y);
    void loadMap(std::string mapFileName);
    void initializeMapArray(sf::Vector2i SizeXY);

    void draw(sf::RenderWindow* window);

    sf::Vector2i getMapTileSize() { return mapTileSize; }
    sf::Vector2i getMapSize() { return mapSize; }
    sf::Vector2f getScenaSize() { return scenaSize; }
    char** getMapArray() { return mapArray; }
    std::string getnameMap() { return nameMap; }

    int height = 0;
    int width = 0;
    std::string nameMap;

    sf::Texture* texture;
    sf::Texture mapTexture;
    sf::Image mapImage;
    sf::Sprite mapSprite;

    sf::Vector2i mapSize;
    sf::Vector2i mapTileSize = { 64, 64 };
    sf::Vector2f scenaSize;
    char** mapArray = nullptr;
};
