#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Player.hpp"

class Camera final {
public:
    Camera(sf::RenderWindow& window, Player& player);
    void handleEvent(sf::Event& e);
    void update(float delta);
    void setMap(Map* map);

private:
    sf::RenderWindow& _window;
    sf::View _view;
    Map* _map;
    Player& _player;
};
