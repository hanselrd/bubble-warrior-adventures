#include "Player.hpp"
#include <iostream>

Player::Player(std::string file_path, std::string player_name, int sprite_format) : Entity(file_path, sprite_format) {
    // Set up initial stats
    Player::defaultPlayerStats();
    _intRect= sf::IntRect(0, sprite_format * 8, sprite_format, sprite_format);
    _name = player_name;
    _attackDamage = 1;
    _experience = 0.0f;
    noKeyWasPressed = true;
}
void Player::levelUp() {
    // Increase the experience cap and reset current exp to 0;
    _maxExperience = std::ceil(_maxExperience * 1.1);
    _experience = 0.0f;
    _level += 1;

    if (_level % 5 == 0) {
        _movementSpeed += 0.05f;
    }
    _maxMana += 10;
    _mana += 10;

    _maxHealth += 10;
    _health += 10;
}
void Player::defaultPlayerStats() {
    _level = 1;
    _experience = 0;
    _maxExperience = 20;
    _health = 10;
    _maxHealth = 10;
    _mana = 10;
    _maxMana = 10;
    _movementSpeed = 1.0f;
    _armor = 0.0f;
}
unsigned Player::getMaxMana() {
    return _maxMana;
}
unsigned Player::getMaxHealth() {
    return _maxHealth;
}
unsigned Player::getMaxExperience() {
    return _maxExperience;
}
unsigned Player::getMana() {
    return _mana;
}
unsigned Player::getHealth() {
    return _health;
}
unsigned Player::getExperience() {
    return _experience;
}
std::string Player::getName() {
    return _name;
}
void Player::handleEvent(sf::Event &e) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _isLooped = true;
        noKeyWasPressed = false;
        _currentAnimation = &_walkingLeft;
        _facing = LEFT;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _isLooped = true;
        noKeyWasPressed = false;
        _currentAnimation = &_walkingRight;
        _facing = RIGHT;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _isLooped = true;
        noKeyWasPressed = false;
        _currentAnimation = &_walkingUp;
        _facing = UP;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _isLooped = true;
        noKeyWasPressed = false;
        _currentAnimation = &_walkingDown;
        _facing = DOWN;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        levelUp();
        std::cout << "Level: " << _level << " Health: " << _maxHealth << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        if (_health >= 5) {
            _health -= 5;
            std::cout << "Been damaged by 5hp. Health:" << _health << std::endl;
        }
        else {
            std::cout << "You died. Health: " << _health << std::endl;
        }
    }
    else {    
        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            stop();
        }
        noKeyWasPressed = true;
        _isLooped = false;
    }
}