#include "Player.hpp"
#include <iostream>

Player::Player(std::string file_path, int sprite_format) : Entity(file_path, sprite_format) {
    // Set up initial stats
    Player::defaultPlayerStats();
}
void Player::levelUp() {
    if (_level % 5 == 0) {
        _movementSpeed += 0.05f;
    }
}
void Player::animateLeft() {

    if (_animationClock.getElapsedTime().asSeconds() > 0.05f) {
           
            // If the animation is at its end or not facing correct direction, 
            // start the animation at the first frame
            if (_sprite.getTextureRect().top != (64 * 9) || _sprite.getTextureRect().left == (64 * 8)) {
                // _spriteFormat = after non-standing frame (second frame 64 * 1)
                // _spriteFormat * 9 = 9th frame down of sprite sheet (64 * 9)
                sf::Vector2i new_rect_coords = sf::Vector2i((_spriteFormat * 1), (_spriteFormat * 9));
                sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);

                _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
            }
        
            // If the sprite is somewhere in the loop, progress it
            else {
                sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
                sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);
                _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
           
        }
        _animationClock.restart();
    }

}
void Player::animateRight() {
    if (_animationClock.getElapsedTime().asSeconds() > 0.05f) {

        // If the animation is at its end or not facing correct direction, 
        // start the animation at the first frame
        if (_sprite.getTextureRect().top != (64 * 11) || _sprite.getTextureRect().left == (64 * 8)) {
            // _spriteFormat = after non-standing frame (second frame 64 * 1)
            // _spriteFormat * 11 = 11th frame down of sprite sheet (64 * 11)
            sf::Vector2i new_rect_coords = sf::Vector2i((_spriteFormat * 1), (_spriteFormat * 11));
            sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);

            _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
        }

        // If the sprite is somewhere in the loop, progress it
        else {
            sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
            sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);
            _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));

        }
        _animationClock.restart();
    }
} 
void Player::animateUp() {
    if (_animationClock.getElapsedTime().asSeconds() > 0.05f) {

        // If the animation is at its end or not facing correct direction, 
        // start the animation at the first frame
        if (_sprite.getTextureRect().top != (64 * 8) || _sprite.getTextureRect().left == (64 * 8)) {
            // _spriteFormat = after non-standing frame (second frame 64 * 1)
            // _spriteFormat * 8 = 8th frame down of sprite sheet (64 * 8)
            sf::Vector2i new_rect_coords = sf::Vector2i((_spriteFormat * 1), (_spriteFormat * 8));
            sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);

            _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
        }

        // If the sprite is somewhere in the loop, progress it
        else {
            sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
            sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);
            _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));

        }
        _animationClock.restart();
    }

}
void Player::animateDown() {
    if (_animationClock.getElapsedTime().asSeconds() > 0.05f) {

        // If the animation is at its end or not facing correct direction, 
        // start the animation at the first frame
        if (_sprite.getTextureRect().top != (64 * 10) || _sprite.getTextureRect().left == (64 * 8)) {
            // _spriteFormat = after non-standing frame (second frame 64 * 1)
            // _spriteFormat * 10 = 10th frame down of sprite sheet (64 * 10)
            sf::Vector2i new_rect_coords = sf::Vector2i((_spriteFormat * 1), (_spriteFormat * 10));
            sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);

            _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
        }

        // If the sprite is somewhere in the loop, progress it
        else {
            sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
            sf::Vector2i new_rect_dimensions = sf::Vector2i(_spriteFormat, _spriteFormat);
            _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));

        }
    }
    _animationClock.restart();
}
/*
* This function changes the current sf::IntRect being shown on the sprite to the 
* left most (x=0) position for that direction (y = 64 * n) on the sprite sheet.
*/
void Player::animateStanding() {
    sf::IntRect current_sprite = _sprite.getTextureRect();
    
    // Player facing up
    if (current_sprite.top == (_spriteFormat * 8)) {
        sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
        sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
        _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));  
    }
    // Player facing left
    else if (current_sprite.top == (_spriteFormat * 9)) {
        sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
        sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
        _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
    }
    // Player facing down
    else if (current_sprite.top == (_spriteFormat * 10)) {
        sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
        sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
        _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions)); 
    }
    // Player facing right
    else if (current_sprite.top == (_spriteFormat * 11)) {
        sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
        sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
        _sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
    }
}
void Player::defaultPlayerStats() {
    _level = 1;
    _experience = 0;
    _maxExperience = 10000;
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
        animateLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        animateRight();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        animateUp();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        animateDown();
    }
    else {
        animateStanding();
    }

    _animationClock.restart();
}