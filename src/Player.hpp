#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Player final : public Entity {
public:
    Player();
    void handleEvent(sf::Event& e);
    void update(float delta);
};
