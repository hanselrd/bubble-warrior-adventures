#include "Player.hpp"
#include <iostream>

Player::Player(std::string file_path, int sprite_format) : Entity(file_path, sprite_format) {
    // Set up initial stats
    Player::defaultPlayerStats();
    _intRect= sf::IntRect(0, 64 * 8, 64, 64);
    _attackDamage = 1;
}
void Player::levelUp() {
    // Increase the experience cap and reset current exp to 0;
    _maxExperience *= 1.3;
    _experience = 0;

    if (_level % 5 == 0) {
        _movementSpeed += 0.05f;
    }
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
void Player::handleEvent(sf::Event &e) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _currentAnimation = &_walkingLeft;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _currentAnimation = &_walkingRight;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _currentAnimation = &_walkingUp;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _currentAnimation = &_walkingDown;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        levelUp();
    }
    else {
    }
    play(*_currentAnimation);

}