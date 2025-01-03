#pragma once
#include <SFML/Graphics.hpp>

class Camera{
public:
	sf::View view;
	sf::Vector2f scenaSize;
	Camera(sf::Vector2f cameraSize, sf::Vector2f scenaSize);
	void setSceneSize(sf::Vector2f scenaSize);
	sf::View* getView();
	void setZoom(float scale);
	void setCenter(sf::Vector2f centerCameraPositionXY);
	sf::Vector2f cameraPositionCorrection(sf::Vector2f centerCameraPositionXY);
};
