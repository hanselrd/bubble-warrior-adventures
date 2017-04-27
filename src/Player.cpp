#include "Player.hpp"
#include <cmath>

Player::Player(std::string filePath, std::string playerName, unsigned spriteFormat)
    : Entity(filePath, spriteFormat) {
    _level = 1;
    _exp = 0;
    _maxExp = 20;
    _health = 10;
    _maxHealth = 10;
    _mana = 10;
    _maxMana = 10;
    _velocity = sf::Vector2f(70.0f, 70.0f);
    _armor = 0.0f;
    _intRect = sf::IntRect(0, spriteFormat * 8, spriteFormat, spriteFormat);
    _name = playerName;
    _attackDamage = 1;
    _noKeyWasPressed = true;
	_isAttacking = false;
    _sprite.setOrigin(0- (float)_intRect.width / 2.0f, 0- (float)_intRect.height / 2.0f);

    _attackUp.setSpriteSheet(_texture);
    _attackUp.addFrame(sf::IntRect(((64 * 3) * 0), (64 * 22), (64 * 3), (64 * 1)));
    _attackUp.addFrame(sf::IntRect(((64 * 3) * 1), (64 * 22), (64 * 3), (64 * 1)));
    _attackUp.addFrame(sf::IntRect(((64 * 3) * 2), (64 * 22), (64 * 3), (64 * 1)));
    _attackUp.addFrame(sf::IntRect(((64 * 3) * 3), (64 * 22), (64 * 3), (64 * 1)));
    _attackUp.addFrame(sf::IntRect(((64 * 3) * 4), (64 * 22), (64 * 3), (64 * 1)));
    _attackUp.addFrame(sf::IntRect(((64 * 3) * 5), (64 * 22), (64 * 3), (64 * 1)));

    _attackLeft.setSpriteSheet(_texture);
    _attackLeft.addFrame(sf::IntRect(((64 * 3) * 0), (64 * 25), 64 * 3, 64 * 1));
    _attackLeft.addFrame(sf::IntRect(((64 * 3) * 1), (64 * 25), 64 * 3, 64 * 1));
    _attackLeft.addFrame(sf::IntRect(((64 * 3) * 2), (64 * 25), 64 * 3, 64 * 1));
    _attackLeft.addFrame(sf::IntRect(((64 * 3) * 3), (64 * 25), 64 * 3, 64 * 1));
    _attackLeft.addFrame(sf::IntRect(((64 * 3) * 4), (64 * 25), 64 * 3, 64 * 1));
    _attackLeft.addFrame(sf::IntRect(((64 * 3) * 5), (64 * 25), 64 * 3, 64 * 1));

    _attackDown.setSpriteSheet(_texture);
    _attackDown.addFrame(sf::IntRect(((64 * 3) * 0), (64 * 28), 64 * 3, 64 * 1));
    _attackDown.addFrame(sf::IntRect(((64 * 3) * 1), (64 * 28), 64 * 3, 64 * 1));
    _attackDown.addFrame(sf::IntRect(((64 * 3) * 2), (64 * 28), 64 * 3, 64 * 1));
    _attackDown.addFrame(sf::IntRect(((64 * 3) * 3), (64 * 28), 64 * 3, 64 * 1));
    _attackDown.addFrame(sf::IntRect(((64 * 3) * 4), (64 * 28), 64 * 3, 64 * 1));
    _attackDown.addFrame(sf::IntRect(((64 * 3) * 5), (64 * 28), 64 * 3, 64 * 1));

    _attackRight.setSpriteSheet(_texture);
    _attackRight.addFrame(sf::IntRect(((64 * 3) * 0), (64 * 31), 64 * 3, 64 * 1));
    _attackRight.addFrame(sf::IntRect(((64 * 3) * 1), (64 * 31), 64 * 3, 64 * 1));
    _attackRight.addFrame(sf::IntRect(((64 * 3) * 2), (64 * 31), 64 * 3, 64 * 1));
    _attackRight.addFrame(sf::IntRect(((64 * 3) * 3), (64 * 31), 64 * 3, 64 * 1));
    _attackRight.addFrame(sf::IntRect(((64 * 3) * 4), (64 * 31), 64 * 3, 64 * 1));
    _attackRight.addFrame(sf::IntRect(((64 * 3) * 5), (64 * 31), 64 * 3, 64 * 1));
}

void Player::handleEvent(sf::Event& e) {}

void Player::update(float delta) {

    if (isAttacking() && !isPlaying())
        _isAttacking = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isAttacking()) {
        move(0, -_velocity.y * delta);
        _isLooped = true;
        _noKeyWasPressed = false;
        _currentAnimation = &_walkingUp;
        _direction = Direction::Up;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isAttacking()) {
        move(-_velocity.x * delta, 0);
        _isLooped = true;
        _noKeyWasPressed = false;
        _currentAnimation = &_walkingLeft;
        _direction = Direction::Left;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isAttacking()) {
        move(0, _velocity.y * delta);
        _isLooped = true;
        _noKeyWasPressed = false;
        _currentAnimation = &_walkingDown;
        _direction = Direction::Down;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isAttacking()) {
        move(_velocity.x * delta, 0);
        _isLooped = true;
        _noKeyWasPressed = false;
        _currentAnimation = &_walkingRight;
        _direction = Direction::Right;
        play(*_currentAnimation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !isAttacking()) {
		_isAttacking = true;
        // Error handling for the different animation lengths
        if (_currentFrame != 0 && !isAttacking()) {
            _currentFrame = 0;
        }
        if (_currentFrame >= _currentAnimation->getSize()) {
            _currentFrame = 0;
        }
        _isLooped = true;
        _noKeyWasPressed = false;
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
    /*
    *   "Cheat codes" for testing
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        levelUp();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        if (_health >= 5) {
            _health -= 5;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !isAttacking()) {
        _isAttacking = true;
        // Error handling for the different animation lengths
        if (_currentFrame != 0 && !isAttacking()) {
            _currentFrame = 0;
        }
        _isLooped = true;
        _noKeyWasPressed = false;
        if (_direction == Direction::Up) {
            _currentAnimation = &_attackUp;
        }
        else if (_direction == Direction::Left) {
            _currentAnimation = &_attackLeft;
        }
        else if (_direction == Direction::Down) {
            _currentAnimation = &_attackDown;
        }
        else if (_direction == Direction::Right) {
            _currentAnimation = &_attackRight;
        }
        play(*_currentAnimation);
    }
    Entity::update(delta);
    if (_noKeyWasPressed && !isAttacking()) {
        _currentFrame = 0;
        stop();
    }
    _noKeyWasPressed = true;
    _isLooped = false;
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
    _maxExp = std::ceil(_maxExp * 1.1f);
    _exp = 0.0f;
    _level += 1;

    if (_level % 5 == 0) {
        _velocity.x += 0.05f;
        _velocity.y += 0.05f;
    }
    _maxMana += 10;
    _mana += 10;

    _maxHealth += 10;
    _health += 10;
}
