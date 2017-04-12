#include "Entity.hpp"

Entity::Entity(std::string file_path, int sprite_format) {
    _texture.loadFromFile("assets/sprites/" + file_path);
    _sprite.setTexture(_texture);
    _intRect = sf::IntRect(0, (sprite_format * 10), sprite_format, sprite_format);
    _sprite.setTextureRect(_intRect);
    _spriteFormat = sprite_format;
    _level = 1;
    _health = 10;
    _facing = directions::DOWN;
    _frameDelay = 0.02f;
    _currentFrame = 0;
    _name = "null";
    
    Entity::loadAnimations();
}

Entity::~Entity() {}

unsigned Entity::getLevel() {
    return _level;
}
sf::FloatRect Entity::getLocalBounds() const {
    return _sprite.getLocalBounds();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_animation && &_tempTexture)
    {
        states.transform *= getTransform();
        states.texture = _tempTexture;
        target.draw(_sprite, states);
    }
}

sf::IntRect Entity::getIntRect() {
    return _intRect;
}

// All animation stuff

void Entity::setAnimation(const Animation& animation)
{
    _animation = &animation;
    setFrame(_currentFrame);
}

void Entity::setFrameTime(float time)
{
    _frameDelay = time;
}

void Entity::play()
{
    _isPaused = false;
}

void Entity::play(const Animation& animation)
{
    if (getAnimation() != &animation)
        setAnimation(animation);
    play();
}

void Entity::pause()
{
    _isPaused = true;
}

void Entity::stop()
{
    _isPaused = true;
    if (_facing == UP) {
        _currentFrame = 0;
    }
    else if (_facing == LEFT) {
        _currentFrame = 1;
    }
    else if (_facing == DOWN) {
        _currentFrame = 2;
    }
    else if (_facing == RIGHT) {
        _currentFrame = 3;
    }

    setAnimation(_standing);
}

const Animation* Entity::getAnimation() const
{
    return _animation;
}

bool Entity::isPlaying() const
{
    return !_isPaused;
}

void Entity::setFrame(std::size_t newFrame)
{
    if (_animation)
    {
        //calculate new vertex positions and texture coordiantes
        sf::IntRect rect = _animation->getFrame(newFrame);
        _intRect = rect;
        _sprite.setTextureRect(rect);
    }

}

void Entity::update(float deltaTime)
{
    if (!_isPaused && _animation)
    {
        _frameDelay += deltaTime;

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
                if (!_isLooped)
                {
                    sf::IntRect temp = _sprite.getTextureRect();
                    temp.left = 0;
                    _intRect = temp;
                    _isPaused = true;
                }
            }
        }

        // set the current frame, not reseting the time
        setFrame(_currentFrame);
    }

}

void Entity::loadAnimations() {

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