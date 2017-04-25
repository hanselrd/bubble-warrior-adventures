#pragma once
#include <SFML/System.hpp>
#include "Animation.hpp"
#include "Entity.hpp"
#include "Inventory.hpp"

class Player : public Entity {
public:
    Player(std::string file_path, std::string player_name, int sprite_format);
    void handleEvent(sf::Event &e);

    unsigned getMana();
    unsigned getHealth();
    unsigned getMaxMana();
    unsigned getMaxHealth();
    float getExperience();
    float getMaxExperience();
    bool isAttacking();
    std::string getName();
private:
    
    unsigned _mana;
    unsigned _maxMana, _maxHealth;
    unsigned _attackDamage;
    float _experience, _maxExperience;
    float _armor;

    bool _isAttacking;
    bool _noKeyWasPressed;

    Inventory _inventory;

    void levelUp();
    void defaultPlayerStats();
    void loadAttackAnimations();

    Animation _attackUp;
    Animation _attackLeft;
    Animation _attackDown;
    Animation _attackRight;
};