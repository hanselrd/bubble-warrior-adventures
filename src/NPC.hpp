#pragma once
#include "Entity.hpp"

class NPC : public Entity {
public:
    NPC();
    NPC(sf::IntRect);
    NPC(std::string filePath, std::string enemyName, unsigned spriteFormat);

    void update(float delta);

    void interact();
};