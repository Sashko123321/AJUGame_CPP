#include "Text.h"

Text::Text(std::string fontFileName, std::wstring textString) {
    font.loadFromFile(fontDirectPath + fontFileName);
    text.setFont(font);
    setString(textString);
    text.setFillColor(sf::Color(128, 125, 125));
}

void Text::setString(std::wstring textString) {
    text.setString(textString);
}

void Text::setPosition(sf::Vector2f textPosition) {
    text.setPosition(textPosition);
}

void Text::draw(sf::RenderWindow* window) {
    window->draw(text);
}
