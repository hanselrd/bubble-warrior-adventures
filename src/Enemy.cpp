#include "Enemy.hpp"
#include "Entity.hpp"

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

void Enemy::update(float delta) {
    // If you are not attacking or game is paused, set attacking to false
    if (!isPlaying()) {
        _isLooped = false;
    }

    //*insert code for following player/interaction here*
}