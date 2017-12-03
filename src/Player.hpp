#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Player final : public Entity {
public:
    explicit Player(std::string filePath, std::string playerName, unsigned spriteFormat);
    void handleEvent(sf::Event& e);
    void update(float delta);
    unsigned getMana() const;
    unsigned getMaxMana() const;
    unsigned getMaxHealth() const;
    float getExp() const;
    float getMaxExp() const;
    bool isAttacking() const;
    const std::string& getName() const;
    void levelUp();

private:
    unsigned _mana, _maxMana, _maxHealth;
    unsigned _attackDamage;
    float _exp, _maxExp;
    float _armor;
    std::string _name;

    bool _isAttacking, _noKeyPressed;

    Animation _attackUp;
    Animation _attackLeft;
    Animation _attackDown;
    Animation _attackRight;
};
