#include "Entity.hpp"
#include "Map.hpp"
#include <cereal/archives/json.hpp>
#include <fstream>

Entity::Entity(const std::string& fileName, int spriteFormat) {
    //  Error prevention by the input if missing .png
    if (fileName.find(".png")) {
        _filePath = fileName;
        _name = fileName.substr(0, fileName.size() - 4);
        _filePath = fileName;
    }
    else {
        _name = fileName;
        _filePath = fileName + ".png";
    }
    _texture.loadFromFile("assets/sprites/" + fileName);
    _spriteFormat = spriteFormat;
    _sprite.setTexture(_texture);
    _intRect = sf::IntRect(0, (spriteFormat * 8), spriteFormat/2, spriteFormat);
    _sprite.setTextureRect(_intRect);

    _level = 1;
    _health = 10;
    _frameDelay = 0.02f;
    _currentFrame = 0;

    _direction = Direction::Down;
    _entityType = EntityType::Object;

    generateWalkAnimations(spriteFormat);
    generateAttackAnimations(spriteFormat);

    _sprite.setOrigin(_spriteFormat / 2.0f, _spriteFormat / 2.0f);
}
Entity::Entity(sf::IntRect) :
    Entity() {
}
Entity::Entity(Map::Object mapObject){
    _spriteFormat = 64;
    _texture.loadFromFile(mapObject.getName() + ".png");
    _sprite.setTexture(_texture);
    _intRect = sf::IntRect(0, (_spriteFormat * 8), _spriteFormat, _spriteFormat);
    _name = mapObject.getName();
    _filePath = "assets/sprites/" + mapObject.getName();

    setPosition(mapObject.getPosition());
    //_sprite.move(-64, -32);
    _level = 1;
    _health = 10;
    _frameDelay = 0.02f;
    _currentFrame = 0;
    _direction = Direction::Down;
    _entityType = EntityType::Object;
    generateWalkAnimations(64);
    generateAttackAnimations(64);

    _sprite.setOrigin(_spriteFormat / 2.0f, _spriteFormat / 2.0f);
}
Entity::Entity() {
    _texture.loadFromFile("assets/sprites/golden_hero_male.png");
    _spriteFormat = 64;
    _name = "null";
    _sprite.setTexture(_texture);
    _filePath = "assets/sprites/golden_hero_male";
    _intRect = sf::IntRect(0, (_spriteFormat * 8), _spriteFormat, _spriteFormat);
    _sprite.setTextureRect(_intRect);

    _level = 1;
    _health = 10;
    _direction = Direction::Down;
    _frameDelay = 0.02f;
    _currentFrame = 0;
    _entityType = EntityType::Object;
    generateWalkAnimations(_spriteFormat);
    generateAttackAnimations(_spriteFormat);

    _sprite.setOrigin(_spriteFormat / 2.0f, _spriteFormat / 2.0f);
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

bool Entity::checkCollision(const Entity& first,const Entity& second, sf::FloatRect& intersection) {
    if (first.getGlobalBounds().intersects(second.getGlobalBounds(), intersection)) {
        switch (second._entityType) {
        case EntityType::NPC:

            break;
        default:
            break;
        } // End switch
        return true;
    }

    else {
        return false;
    }
}
void Entity::modifyHealth(int delta, bool healing) {
    // delta means amount of hp to change
    // healing = truefi means the target is healing 'delta' amount of hp
    // healing = false means the target is removing 'delta' amount of hp from self

    // if the target is healing
    if (healing) {
        _health += delta;
    }
    // if the target is taking damage
    else {
        _health -= delta;
    }
}
void Entity::update(float delta) {
    if (!_isPaused && _animation) {
        _frameDelay += delta;

        if (!isAttacking()) {
            _sprite.setTextureRect(sf::IntRect(0, 0, 32, 64));
            //(_sprite.getGlobalBounds().left, _sprite.getGlobalBounds().top);
        }

        if (_frameDelay > 0.10f) {
            // Gwet next Frame index
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
        // Set the current frame, not reseting the time
        setFrame(_currentFrame);

        //// Necessary to prevent sprite from "jumping" locations when attacking
        _sprite.setOrigin(_intRect.width /2.0f, _intRect.height /2.0f); 
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
		//_sprite.setTextureRect(_intRect);
        // Prevents the sprite from jumping when going back to standing
		_sprite.setOrigin(_intRect.width / 2.0f, _intRect.height / 2.0f);
        //_sprite.setPosition(_sprite.getPosition().x + 64, _sprite.getPosition().y);
		setAnimation(_standing);
	}
}

void Entity::setName(std::string string) {
    _name = string;
}

void Entity::setAttacking(bool b) {
    _isAttacking = b;
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
    pause();
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

sf::Vector2f Entity::getBaseWalkSpeed() const {
    return _walkSpeed;
}

void Entity::setHealth(unsigned val) {
    _health = val;
}

void Entity::setLevel(unsigned val) {
    _level = val;
}

bool Entity::isDead() {
    if (_health <= 0) {
        return true;
    }
    else {
        return false;
    }
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    if (_spriteFormat > 0) {
        sf::Sprite temp(_sprite);
        //temp.setOrigin(_spriteFormat / 2.0f, _spriteFormat / 2.0f);
        target.draw(temp, states);
    }
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
