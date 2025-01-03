#include "Camera.h"

Camera::Camera(sf::Vector2f cameraSize, sf::Vector2f scenaSize){
	view.reset(sf::FloatRect(0, 0, cameraSize.x, cameraSize.y));
	setSceneSize(scenaSize);
}
void Camera::setSceneSize(sf::Vector2f scenaSize) {
	this->scenaSize = scenaSize;
}
sf::View* Camera::getView() { return &view; }
void Camera::setZoom(float scale) {
	view.zoom(scale);
	sf::Vector2f tempVector = view.getSize();
	if (tempVector.x > scenaSize.x)
		tempVector.x = scenaSize.x;
	if (tempVector.y > scenaSize.y)
		tempVector.y = scenaSize.y;
	view.setSize(tempVector);
}
void Camera::setCenter(sf::Vector2f centerCameraPositionXY) {
	centerCameraPositionXY = cameraPositionCorrection(centerCameraPositionXY);
	view.setCenter(centerCameraPositionXY);
}
sf::Vector2f Camera::cameraPositionCorrection(sf::Vector2f centerCameraPositionXY) {
	if (centerCameraPositionXY.x - view.getSize().x / 2 < 0)
		centerCameraPositionXY.x = view.getSize().x / 2;
	if (centerCameraPositionXY.x + view.getSize().x / 2 > scenaSize.x)
		centerCameraPositionXY.x = scenaSize.x - view.getSize().x / 2;
	if (centerCameraPositionXY.y - view.getSize().y / 2 < 0)
		centerCameraPositionXY.y = view.getSize().y / 2;
	if (centerCameraPositionXY.y + view.getSize().y / 2 > scenaSize.y)
		centerCameraPositionXY.y = scenaSize.y - view.getSize().y / 2;
	return centerCameraPositionXY;
};
