#pragma once
#include "Entity.hpp"
#include <iostream>

class Enemy : public Entity {
public:
    explicit Enemy(std::string filePath, std::string enemyName, unsigned spriteFormat);

private:
    int _expDropped;
    float _attackStrength;
    bool _attack; //true = is attacking
};