#pragma once
#include "Entity.hpp"
#include <SFML/System.hpp>

class Player : public Entity {
public:
    Player(std::string file_path, int sprite_format);
    std::string getLevel();
    void handleEvent(sf::Event &e);

private:
    
    unsigned _mana, _experience, _level;
    unsigned _maxMana, _maxHealth, _maxExperience;
    unsigned _attackDamage;
    float _movementSpeed, _armor;

    sf::Clock _animationClock;

    void levelUp();
    void defaultPlayerStats();
    void animateLeft();
    void animateRight();
    void animateUp();
    void animateDown();
    void animateStanding();
};