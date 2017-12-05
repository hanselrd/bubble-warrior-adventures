#pragma once
#include "Entity.hpp"
#include <iostream>

class Enemy : public Entity {
public:
    Enemy(std::string filePath, std::string enemyName, unsigned spriteFormat);

    void update(float delta);

private:
    int _expDropped;
    float _attackStrength;
    bool _attack; //true = is attacking
};