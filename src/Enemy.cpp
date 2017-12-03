#include "Enemy.hpp"

Enemy::Enemy(std::string filePath, std::string enemyName, unsigned spriteFormat)
    : Entity(filePath, spriteFormat)
{
    _intRect = sf::IntRect(0, spriteFormat * 8, spriteFormat, spriteFormat);
    _level = 1; 
    _health = 1;
    _expDropped = 1;
    _attackStrength = 1;
    _attack = true;

}
