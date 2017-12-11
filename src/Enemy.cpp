#include "Enemy.hpp"
#include "Entity.hpp"

Enemy::Enemy(std::string filePath, std::string enemyName, unsigned spriteFormat)
    : Entity(filePath, spriteFormat) 
{
    _level = 1; 
    _health = 1;
    _expDropped = 1;
    _attackStrength = 1;
    _entityType = EntityType::Enemy;
    _isAttacking = true;    
    
    //Green Slime Initializations
    for (int i = 1; i < 30; i++) {
        if (_name == "GreenSlime" + i) {
            _name = "GreenSlime" + i;
        }
    }
}

void Enemy::update(float delta) {
    // If you are not attacking or game is paused, set attacking to false
    if (!isPlaying()) {
        _isLooped = false;
        _isAttacking = false;
    }
    if (isPlaying() && _animation) {
        _frameDelay += delta;

        if (_frameDelay > 0.10f) {
            // get next Frame index
            if (_currentFrame + 1 < _currentAnimation->getSize()) {
                _currentFrame++;
                _frameDelay = 0; // reset to start
            }
            else {
                // Animation has ended
                _currentFrame = 0;
                // Entity stops moving
                if (!_isLooped) {
                    sf::IntRect temp = _sprite.getTextureRect();
                    temp.left = 0;
                    _intRect = temp;
                    _isPaused = true;
                    _isLooped = false;
                }
                _frameDelay = 0;
            }
        }
        // set the current frame, not reseting the time
        setFrame(_currentFrame);
        _sprite.setOrigin(_intRect.width / 2.0f, _intRect.height / 2.0f);
    }
    // If it is paused, reset to standing
    else {
        if (_direction == Direction::Up)
            _currentFrame = 0;
        else if (_direction == Direction::Left)
            _currentFrame = 1;
        else if (_direction == Direction::Down)
            _currentFrame = 2;
        else if (_direction == Direction::Right)
            _currentFrame = 3;
        _intRect.width = _spriteFormat;
        _intRect.height = _spriteFormat;
        _sprite.setTextureRect(_intRect);
        _sprite.setOrigin(_intRect.width / 2.0f, _intRect.height / 2.0f);
        setAnimation(_standing);
    }
}