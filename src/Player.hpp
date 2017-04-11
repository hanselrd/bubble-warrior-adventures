#pragma once
#include "Entity.hpp"
#include <SFML/System.hpp>

class Player : public Entity {
public:
    Player(std::string file_path, int sprite_format);
    void handleEvent(sf::Event &e);

    unsigned getMaxMana();
    unsigned getMaxHealth();
    unsigned getMaxExperience();
    unsigned getMana();
    unsigned getHealth();
    unsigned getExperience();
private:
    
    unsigned _mana, _experience;
    unsigned _maxMana, _maxHealth, _maxExperience;
    unsigned _attackDamage;
    float _movementSpeed, _armor;
    bool noKeyWasPressed;

    void levelUp();
    void defaultPlayerStats();
};