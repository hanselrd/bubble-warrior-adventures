#include "Camera.hpp"

#define CAMERA_ZOOM_FACTOR 0.5f

Camera::Camera(sf::RenderWindow& window, Player& player)
    : _player(player)
    , _window(window) {
    _view.setSize((float)window.getSize().x, (float)window.getSize().y);
    _view.zoom(CAMERA_ZOOM_FACTOR);
}

void Camera::handleEvent(sf::Event& e) {}

void Camera::update(float delta) {
    auto playerPos = _player.getGlobalBounds();
    auto windowSize = _window.getSize();

    _view.setCenter(sf::Vector2f(_player.getGlobalBounds().left,_player.getGlobalBounds().top));

    if (playerPos.left < (windowSize.x / 2.0f) * CAMERA_ZOOM_FACTOR)
        _view.setCenter((windowSize.x / 2.0f) * CAMERA_ZOOM_FACTOR, _view.getCenter().y);

    if (playerPos.top < (windowSize.y / 2.0f) * CAMERA_ZOOM_FACTOR)
        _view.setCenter(_view.getCenter().x, (windowSize.y / 2.0f) * CAMERA_ZOOM_FACTOR);

    if (playerPos.left > _map->getSize().x - ((windowSize.x / 2.0f) * CAMERA_ZOOM_FACTOR))
        _view.setCenter(_map->getSize().x - ((windowSize.x / 2.0f) * CAMERA_ZOOM_FACTOR), _view.getCenter().y);

    if (playerPos.top > _map->getSize().y - ((windowSize.y / 2.0f) * CAMERA_ZOOM_FACTOR))
        _view.setCenter(_view.getCenter().x, _map->getSize().y - ((windowSize.y / 2.0f) * CAMERA_ZOOM_FACTOR));

    _window.setView(_view);
}

const sf::View& Camera::getView() const {
    return _view;
}

void Camera::setMap(Map* map) {
    _map = map;
}
