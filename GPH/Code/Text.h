#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Text {
public:
    Text(std::string fontFileName, std::wstring textString = L"");
    void setString(std::wstring textString);
    void setPosition(sf::Vector2f textPosition);
    void draw(sf::RenderWindow* window);
    sf::Font font;
    sf::Text text;
    std::string fontDirectPath = "Resours/Textures/game/";
};