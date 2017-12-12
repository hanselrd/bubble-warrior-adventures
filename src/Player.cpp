#include "Player.hpp"
#include <iostream>
#include <cmath>

Player::Player(std::string filePath, std::string playerName, unsigned spriteFormat)
    : Entity(filePath, spriteFormat) {
    _level = 1;
    _maxLevel = 1000;
    _exp = 0;
    _maxExp = 20;
    _health = 10;
    _maxHealth = 10;
    _mana = 10;
    _maxMana = 10;
    _velocity = sf::Vector2f(60.0f, 60.0f);
    _armor = 0.0f;
    _name = playerName;
    _attackDamage = 1;
    _noKeyPressed = true;
	_isAttacking = false;
    _sprite.move(_spriteFormat/2, 0);
    _entityType = EntityType::Player;
    generateAttackAnimations(spriteFormat);
    _name = "Jaime";
}

void Player::handleEvent(sf::Event& e) {}

void Player::update(float delta) {

    // If you are not attacking or game is paused, set attacking to false
    if (!isPlaying()) {
        _isLooped = false;
        _isAttacking = false;
    }
    //**************************************************
    //*ANIMATE**ANIMATE*ANIMATE*ANIMATE*ANIMATE*ANIMATE*
    //**************************************************
    {
        // Update animation
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isAttacking()) {
            _currentAnimation = &_walkingUp;
            _direction = Direction::Up;
            _isLooped = true;
            _noKeyPressed = false;
            play(*_currentAnimation);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isAttacking()) {
            _currentAnimation = &_walkingLeft;
            _direction = Direction::Left;
            _isLooped = true;
            _noKeyPressed = false;
            play(*_currentAnimation);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isAttacking()) {
            _currentAnimation = &_walkingDown;
            _direction = Direction::Down;
            _isLooped = true;
            _noKeyPressed = false;
            play(*_currentAnimation);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isAttacking()) {
            _currentAnimation = &_walkingRight;
            _direction = Direction::Right;
            _isLooped = true;
            _noKeyPressed = false;
            play(*_currentAnimation);
        }

        // Change character movement and include sprinting with Left Shift

        int run_multiplier = 2;

        // If LShift is not pressed, 'run' is off
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            run_multiplier = 1;
        }
        // Move up with 'W' key
        if (_direction == Direction::Up && sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isAttacking()) {
            move(0, -_velocity.y * delta * run_multiplier);
        }
        // Move left with 'A' key
        if (_direction == Direction::Left && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isAttacking()) {
            move(-_velocity.x * delta * run_multiplier, 0);
        }
        // Move down with 'S' key
        if (_direction == Direction::Down && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isAttacking()) {
            move(0, _velocity.y * delta* run_multiplier);
        }
        // Move right with 'D' key
        if (_direction == Direction::Right && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isAttacking()) {
            move(_velocity.x * delta * run_multiplier, 0);
        }
    }
    // End Animate


    //**************************************************
    //*ATTACKING**ATTACKING**ATTACKING*ATTACKING********
    //**************************************************
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !isAttacking()) {
            // Error handling for the different animation lengths
            if (_currentFrame != 0 && !isAttacking()) {
                _currentFrame = 0;
                _isAttacking = true;
            }
            // Check the current frame with the animation queue size.
            // Resets current frame to start of queue.
            if (_currentFrame >= _currentAnimation->getSize()) {
                _currentFrame = 0;
            }
            _isLooped = true;
            _noKeyPressed = false;
            if (_direction == Direction::Up)
                _currentAnimation = &_attackUp;
            else if (_direction == Direction::Left)
                _currentAnimation = &_attackLeft;
            else if (_direction == Direction::Down)
                _currentAnimation = &_attackDown;
            else if (_direction == Direction::Right)
                _currentAnimation = &_attackRight;
            play(*_currentAnimation);
        }
    }
    /*
    *   "Cheat codes" for testing
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        levelUp();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        if (_health >= 1) {
            _health -= 1;
        }
    }
    //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !isAttacking()) {
    //    _isAttacking = true;
    //    // Error handling for the different animation lengths
    //    if (_currentFrame != 0 && !isAttacking()) {
    //        _currentFrame = 0;
    //    }
    //    _isLooped = true;
    //    _noKeyPressed = false;
    //    if (_direction == Direction::Up) {
    //        _currentAnimation = &_attackUp;
    //    }
    //    else if (_direction == Direction::Left) {
    //        _currentAnimation = &_attackLeft;
    //    }
    //    else if (_direction == Direction::Down) {
    //        _currentAnimation = &_attackDown;
    //    }
    //    else if (_direction == Direction::Right) {
    //        _currentAnimation = &_attackRight;
    //    }
    //    play(*_currentAnimation);
    //}
    _isLooped = false;
    Entity::update(delta);
    if (_noKeyPressed && !isAttacking()) {
        // Current frame set to correct standing position
        stop();
    }
    _noKeyPressed = true;
}

unsigned Player::getMana() const {
    return _mana;
}

unsigned Player::getMaxMana() const {
    return _maxMana;
}

unsigned Player::getMaxHealth() const {
    return _maxHealth;
}

float Player::getExp() const {
    return _exp;
}

float Player::getMaxExp() const {
    return _maxExp;
}

bool Player::isAttacking() const {
    return _isAttacking;
}

const std::string& Player::getName() const {
    return _name;
}

void Player::levelUp() {
    // Increase the experience cap and reset current exp to 0;
    _exp = 0.0f;

    _level += 1;
    // EXP calculation
    _maxExp = (float)floor(10 * (_level * 1.10));

    // End EXP calculation
    //if (_level % 3 == 0) {
    //    _velocity = sf::Vector2f(_velocity.x + 0.15f, _velocity.y + 0.15f);
    //}
    _maxMana += 1;
    _mana += 1;

    _maxHealth += 1;
    _health += 1;

    //*********************INSERT GUI BELOW FOR LEVEL UP INFO
    //***********
    //***********
    //***********************************************************************
}
