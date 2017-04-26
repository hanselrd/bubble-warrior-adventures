#include "Entity.hpp"

Entity::Entity(const std::string& filePath, unsigned spriteFormat) {
    _texture.loadFromFile("assets/sprites/" + filePath);
    _sprite.setTexture(_texture);
    _intRect = sf::IntRect(0, (spriteFormat * 10), spriteFormat, spriteFormat);
    _sprite.setTextureRect(_intRect);
    _spriteFormat = spriteFormat;
    _level = 1;
    _health = 10;
    _direction = Direction::Down;
    _frameDelay = 0.02f;
    _currentFrame = 0;

    _walkingUp.setSpriteSheet(_texture);
    _walkingUp.addFrame(sf::IntRect((64 * 1), (64 * 8), 64, 64));
    _walkingUp.addFrame(sf::IntRect((64 * 2), (64 * 8), 64, 64));
    _walkingUp.addFrame(sf::IntRect((64 * 3), (64 * 8), 64, 64));
    _walkingUp.addFrame(sf::IntRect((64 * 4), (64 * 8), 64, 64));
    _walkingUp.addFrame(sf::IntRect((64 * 5), (64 * 8), 64, 64));
    _walkingUp.addFrame(sf::IntRect((64 * 6), (64 * 8), 64, 64));
    _walkingUp.addFrame(sf::IntRect((64 * 7), (64 * 8), 64, 64));
    _walkingUp.addFrame(sf::IntRect((64 * 8), (64 * 8), 64, 64));

    _walkingLeft.setSpriteSheet(_texture);
    _walkingLeft.addFrame(sf::IntRect((64 * 1), (64 * 9), 64, 64));
    _walkingLeft.addFrame(sf::IntRect((64 * 2), (64 * 9), 64, 64));
    _walkingLeft.addFrame(sf::IntRect((64 * 3), (64 * 9), 64, 64));
    _walkingLeft.addFrame(sf::IntRect((64 * 4), (64 * 9), 64, 64));
    _walkingLeft.addFrame(sf::IntRect((64 * 5), (64 * 9), 64, 64));
    _walkingLeft.addFrame(sf::IntRect((64 * 6), (64 * 9), 64, 64));
    _walkingLeft.addFrame(sf::IntRect((64 * 7), (64 * 9), 64, 64));
    _walkingLeft.addFrame(sf::IntRect((64 * 8), (64 * 9), 64, 64));

    _walkingDown.setSpriteSheet(_texture);
    _walkingDown.addFrame(sf::IntRect((64 * 1), (64 * 10), 64, 64));
    _walkingDown.addFrame(sf::IntRect((64 * 2), (64 * 10), 64, 64));
    _walkingDown.addFrame(sf::IntRect((64 * 3), (64 * 10), 64, 64));
    _walkingDown.addFrame(sf::IntRect((64 * 4), (64 * 10), 64, 64));
    _walkingDown.addFrame(sf::IntRect((64 * 5), (64 * 10), 64, 64));
    _walkingDown.addFrame(sf::IntRect((64 * 6), (64 * 10), 64, 64));
    _walkingDown.addFrame(sf::IntRect((64 * 7), (64 * 10), 64, 64));
    _walkingDown.addFrame(sf::IntRect((64 * 8), (64 * 10), 64, 64));

    _walkingRight.setSpriteSheet(_texture);
    _walkingRight.addFrame(sf::IntRect((64 * 1), (64 * 11), 64, 64));
    _walkingRight.addFrame(sf::IntRect((64 * 2), (64 * 11), 64, 64));
    _walkingRight.addFrame(sf::IntRect((64 * 3), (64 * 11), 64, 64));
    _walkingRight.addFrame(sf::IntRect((64 * 4), (64 * 11), 64, 64));
    _walkingRight.addFrame(sf::IntRect((64 * 5), (64 * 11), 64, 64));
    _walkingRight.addFrame(sf::IntRect((64 * 6), (64 * 11), 64, 64));
    _walkingRight.addFrame(sf::IntRect((64 * 7), (64 * 11), 64, 64));
    _walkingRight.addFrame(sf::IntRect((64 * 8), (64 * 11), 64, 64));

    _standing.setSpriteSheet(_texture);
    _standing.addFrame(sf::IntRect(0, (64 * 8), 64, 64));  // Up
    _standing.addFrame(sf::IntRect(0, (64 * 9), 64, 64));  // Left
    _standing.addFrame(sf::IntRect(0, (64 * 10), 64, 64)); // Down
    _standing.addFrame(sf::IntRect(0, (64 * 11), 64, 64)); // Right

    _currentAnimation = &_standing;
}

Entity::Entity(float radius, const sf::Color& color) {
    _circle.setRadius(radius);
    _circle.setFillColor(color);
}

Entity::~Entity() {}

sf::FloatRect Entity::getLocalBounds() const {
    if (_spriteFormat > 0)
        return _sprite.getLocalBounds();
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
