#include "Camera.hpp"

#define CAMERA_ZOOM_FACTOR 0.5

Camera::Camera(sf::RenderWindow& window, Player& player)
    : _player(player)
    , _window(window) {
    _view.setSize(window.getSize().x, window.getSize().y);
    _view.zoom(CAMERA_ZOOM_FACTOR);
}

void Camera::handleEvent(sf::Event& e) {}

void Camera::update(float delta) {
    auto playerBounds = _player.getGlobalBounds();
    auto windowSize = _window.getSize();

    _view.setCenter(_player.getPosition());

    if (playerBounds.left < (windowSize.x / 2) * CAMERA_ZOOM_FACTOR)
        _view.setCenter((windowSize.x / 2) * CAMERA_ZOOM_FACTOR, _view.getCenter().y);

    if (playerBounds.top < (windowSize.y / 2) * CAMERA_ZOOM_FACTOR)
        _view.setCenter(_view.getCenter().x, (windowSize.y / 2) * CAMERA_ZOOM_FACTOR);

    if (playerBounds.left + playerBounds.width > (_map->getWidth() * _map->getTileWidth()) - ((windowSize.x / 2) * CAMERA_ZOOM_FACTOR))
        _view.setCenter((_map->getWidth() * _map->getTileWidth()) - ((windowSize.x / 2) * CAMERA_ZOOM_FACTOR), _view.getCenter().y);

    if (playerBounds.top + playerBounds.height > (_map->getHeight() * _map->getTileHeight()) - ((windowSize.y / 2) * CAMERA_ZOOM_FACTOR))
        _view.setCenter(_view.getCenter().x, (_map->getHeight() * _map->getTileHeight()) - ((windowSize.y / 2) * CAMERA_ZOOM_FACTOR));

    _window.setView(_view);
}

void Camera::setMap(Map* map) {
    _map = map;
}
