#pragma once
#include "Entity.hpp"

class NPC final: public Entity {
public:
    NPC();
    NPC(sf::IntRect);
    NPC::NPC(Map::Object mapObject);
    NPC(std::string filePath, std::string enemyName, unsigned spriteFormat);

    void update(float delta);

    void interact();
private:

};