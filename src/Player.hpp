#pragma once
#include "Animation.hpp"
#include <SFML/System.hpp>
#include "Entity.hpp"

class Player : public Entity {
public:
    Player(std::string file_path, std::string player_name, int sprite_format);
    void handleEvent(sf::Event &e);

    unsigned getMaxMana();
    unsigned getMaxHealth();
    unsigned getMaxExperience();
    unsigned getMana();
    unsigned getHealth();
    unsigned getExperience();
    std::string getName();
private:
    
    unsigned _mana, _experience;
    unsigned _maxMana, _maxHealth;
    float _maxExperience;
    unsigned _attackDamage;
    float _movementSpeed, _armor;
    bool noKeyWasPressed;

    void levelUp();
    void defaultPlayerStats();
    void loadAttackAnimations();

    Animation _attackUp;
    Animation _attackLeft;
    Animation _attackDown;
    Animation _attackRight;
};