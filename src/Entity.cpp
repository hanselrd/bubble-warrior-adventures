#include "Entity.hpp"

Entity::Entity(const std::string& filePath, int spriteFormat) {
    _texture.loadFromFile("assets/sprites/" + filePath);
    _sprite.setTexture(_texture);
    _intRect = sf::IntRect(0, (spriteFormat * 8), spriteFormat, spriteFormat);
    _sprite.setTextureRect(_intRect);
    _spriteFormat = spriteFormat;
    _level = 1;
    _health = 10;
    _direction = Direction::Down;
    _frameDelay = 0.02f;
    _currentFrame = 0;

    generateWalkAnimations(spriteFormat);
    generateAttackAnimations(spriteFormat);
}

Entity::Entity() {
    Entity("golden_hero_male_no_shield", 64);
}
Entity::~Entity() {}

sf::FloatRect Entity::getLocalBounds() const {
    if (_spriteFormat > 0) {
        auto temp = _sprite.getLocalBounds();
        temp.width /= 15;
        temp.height /= 2;
        return temp;
    }
    else
        return _circle.getLocalBounds();
}

void Entity::update(float delta) {
    if (!_isPaused && _animation) {
        _frameDelay += delta;

        if (_frameDelay > 0.10f) {
            // get next Frame index
            if (_currentFrame + 1 < _animation->getSize()) {
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

void Entity::setAnimation(const Animation& animation) {
    _animation = &animation;
    setFrame(_currentFrame);
}

void Entity::setFrameTime(float time) {
    _frameDelay = time;
}

void Entity::play() {
    _isPaused = false;
}

void Entity::play(const Animation& animation) {
    if (getAnimation() != &animation)
        setAnimation(animation);
    play();
}

void Entity::pause() {
    _isPaused = true;
}

void Entity::stop() {
    _isPaused = true;
    if (_direction == Direction::Up)
        _currentFrame = 0;
    else if (_direction == Direction::Left)
        _currentFrame = 1;
    else if (_direction == Direction::Down)
        _currentFrame = 2;
    else if (_direction == Direction::Right)
        _currentFrame = 3;
}

const Animation* Entity::getAnimation() const {
    return _animation;
}

bool Entity::isPlaying() const {
    return !_isPaused;
}

void Entity::setFrame(std::size_t n) {
    if (_animation) {
        if (n >= _animation->getSize()) {
            n = 0;
        }
        sf::IntRect rect = _animation->getFrame(n);
        _intRect = rect;
        _sprite.setTextureRect(rect);
    }
}

unsigned Entity::getLevel() const {
    return _level;
}

unsigned Entity::getHealth() const {
    return _health;
}

sf::Vector2f Entity::getVelocity() const {
    return _velocity;
}

void Entity::setHealth(unsigned val) {
    _health = val;
}

void Entity::setLevel(unsigned val) {
    _level = val;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (_spriteFormat > 0)
        target.draw(_sprite, states);
    else
        target.draw(_circle, states);
}

Entity::Direction Entity::getDirection()
{
    return _direction;
}

void Entity::generateWalkAnimations(int spriteFormat) {
    _walkingUp.setSpriteSheet(_texture);
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 1), (spriteFormat * 8), spriteFormat, spriteFormat));
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 2), (spriteFormat * 8), spriteFormat, spriteFormat));
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 3), (spriteFormat * 8), spriteFormat, spriteFormat));
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 4), (spriteFormat * 8), spriteFormat, spriteFormat));
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 5), (spriteFormat * 8), spriteFormat, spriteFormat));
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 6), (spriteFormat * 8), spriteFormat, spriteFormat));
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 7), (spriteFormat * 8), spriteFormat, spriteFormat));
    _walkingUp.addFrame(sf::IntRect((spriteFormat * 8), (spriteFormat * 8), spriteFormat, spriteFormat));

    _walkingLeft.setSpriteSheet(_texture);
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 1), (spriteFormat * 9), spriteFormat, spriteFormat));
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 2), (spriteFormat * 9), spriteFormat, spriteFormat));
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 3), (spriteFormat * 9), spriteFormat, spriteFormat));
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 4), (spriteFormat * 9), spriteFormat, spriteFormat));
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 5), (spriteFormat * 9), spriteFormat, spriteFormat));
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 6), (spriteFormat * 9), spriteFormat, spriteFormat));
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 7), (spriteFormat * 9), spriteFormat, spriteFormat));
    _walkingLeft.addFrame(sf::IntRect((spriteFormat * 8), (spriteFormat * 9), spriteFormat, spriteFormat));

    _walkingDown.setSpriteSheet(_texture);
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 1), (spriteFormat * 10), spriteFormat, spriteFormat));
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 2), (spriteFormat * 10), spriteFormat, spriteFormat));
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 3), (spriteFormat * 10), spriteFormat, spriteFormat));
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 4), (spriteFormat * 10), spriteFormat, spriteFormat));
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 5), (spriteFormat * 10), spriteFormat, spriteFormat));
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 6), (spriteFormat * 10), spriteFormat, spriteFormat));
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 7), (spriteFormat * 10), spriteFormat, spriteFormat));
    _walkingDown.addFrame(sf::IntRect((spriteFormat * 8), (spriteFormat * 10), spriteFormat, spriteFormat));

    _walkingRight.setSpriteSheet(_texture);
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 1), (spriteFormat * 11), spriteFormat, spriteFormat));
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 2), (spriteFormat * 11), spriteFormat, spriteFormat));
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 3), (spriteFormat * 11), spriteFormat, spriteFormat));
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 4), (spriteFormat * 11), spriteFormat, spriteFormat));
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 5), (spriteFormat * 11), spriteFormat, spriteFormat));
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 6), (spriteFormat * 11), spriteFormat, spriteFormat));
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 7), (spriteFormat * 11), spriteFormat, spriteFormat));
    _walkingRight.addFrame(sf::IntRect((spriteFormat * 8), (spriteFormat * 11), spriteFormat, spriteFormat));

    _standing.setSpriteSheet(_texture);
    _standing.addFrame(sf::IntRect(0, (spriteFormat * 8), spriteFormat, spriteFormat));  // Up
    _standing.addFrame(sf::IntRect(0, (spriteFormat * 9), spriteFormat, spriteFormat));  // Left
    _standing.addFrame(sf::IntRect(0, (spriteFormat * 10), spriteFormat, spriteFormat)); // Down
    _standing.addFrame(sf::IntRect(0, (spriteFormat * 11), spriteFormat, spriteFormat)); // Right

    _currentAnimation = &_standing;
}
void Entity::generateAttackAnimations(int spriteFormat)
{
    _attackUp.setSpriteSheet(_texture);
    _attackUp.addFrame(sf::IntRect(((spriteFormat * 3) * 0), (spriteFormat * 22), (spriteFormat * 3), (spriteFormat * 1)));
    _attackUp.addFrame(sf::IntRect(((spriteFormat * 3) * 1), (spriteFormat * 22), (spriteFormat * 3), (spriteFormat * 1)));
    _attackUp.addFrame(sf::IntRect(((spriteFormat * 3) * 2), (spriteFormat * 22), (spriteFormat * 3), (spriteFormat * 1)));
    _attackUp.addFrame(sf::IntRect(((spriteFormat * 3) * 3), (spriteFormat * 22), (spriteFormat * 3), (spriteFormat * 1)));
    _attackUp.addFrame(sf::IntRect(((spriteFormat * 3) * 4), (spriteFormat * 22), (spriteFormat * 3), (spriteFormat * 1)));
    _attackUp.addFrame(sf::IntRect(((spriteFormat * 3) * 5), (spriteFormat * 22), (spriteFormat * 3), (spriteFormat * 1)));

    _attackLeft.setSpriteSheet(_texture);
    _attackLeft.addFrame(sf::IntRect(((spriteFormat * 3) * 0), (spriteFormat * 25), spriteFormat * 3, spriteFormat * 1));
    _attackLeft.addFrame(sf::IntRect(((spriteFormat * 3) * 1), (spriteFormat * 25), spriteFormat * 3, spriteFormat * 1));
    _attackLeft.addFrame(sf::IntRect(((spriteFormat * 3) * 2), (spriteFormat * 25), spriteFormat * 3, spriteFormat * 1));
    _attackLeft.addFrame(sf::IntRect(((spriteFormat * 3) * 3), (spriteFormat * 25), spriteFormat * 3, spriteFormat * 1));
    _attackLeft.addFrame(sf::IntRect(((spriteFormat * 3) * 4), (spriteFormat * 25), spriteFormat * 3, spriteFormat * 1));
    _attackLeft.addFrame(sf::IntRect(((spriteFormat * 3) * 5), (spriteFormat * 25), spriteFormat * 3, spriteFormat * 1));

    _attackDown.setSpriteSheet(_texture);
    _attackDown.addFrame(sf::IntRect(((spriteFormat * 3) * 0), (spriteFormat * 28), spriteFormat * 3, spriteFormat * 1));
    _attackDown.addFrame(sf::IntRect(((spriteFormat * 3) * 1), (spriteFormat * 28), spriteFormat * 3, spriteFormat * 1));
    _attackDown.addFrame(sf::IntRect(((spriteFormat * 3) * 2), (spriteFormat * 28), spriteFormat * 3, spriteFormat * 1));
    _attackDown.addFrame(sf::IntRect(((spriteFormat * 3) * 3), (spriteFormat * 28), spriteFormat * 3, spriteFormat * 1));
    _attackDown.addFrame(sf::IntRect(((spriteFormat * 3) * 4), (spriteFormat * 28), spriteFormat * 3, spriteFormat * 1));
    _attackDown.addFrame(sf::IntRect(((spriteFormat * 3) * 5), (spriteFormat * 28), spriteFormat * 3, spriteFormat * 1));

    _attackRight.setSpriteSheet(_texture);
    _attackRight.addFrame(sf::IntRect(((spriteFormat * 3) * 0), (spriteFormat * 31), spriteFormat * 3, spriteFormat * 1));
    _attackRight.addFrame(sf::IntRect(((spriteFormat * 3) * 1), (spriteFormat * 31), spriteFormat * 3, spriteFormat * 1));
    _attackRight.addFrame(sf::IntRect(((spriteFormat * 3) * 2), (spriteFormat * 31), spriteFormat * 3, spriteFormat * 1));
    _attackRight.addFrame(sf::IntRect(((spriteFormat * 3) * 3), (spriteFormat * 31), spriteFormat * 3, spriteFormat * 1));
    _attackRight.addFrame(sf::IntRect(((spriteFormat * 3) * 4), (spriteFormat * 31), spriteFormat * 3, spriteFormat * 1));
    _attackRight.addFrame(sf::IntRect(((spriteFormat * 3) * 5), (spriteFormat * 31), spriteFormat * 3, spriteFormat * 1));
}