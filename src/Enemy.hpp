#pragma once
#include "Entity.hpp"

class Enemy : public Entity {
public:
    Enemy();
    Enemy(sf::IntRect);
    Enemy::Enemy(Map::Object mapObject);
    Enemy(std::string filePath, std::string enemyName, unsigned spriteFormat);

    void update(float delta);

    int getExpDropped();
    float getAttackStrength();
private:
    int _expDropped;
    float _attackStrength;
};