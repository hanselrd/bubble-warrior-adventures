#include "Entity.hpp"

#include <iostream>

Entity::Entity(std::string file_path, int sprite_format) {
    _texture.loadFromFile("assets/sprites/" + file_path);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, (64 * 10), sprite_format, sprite_format));
    _spriteFormat = sprite_format;
    _level = 1;
    _facing = directions::DOWN;
    _frameDelay = 0.02f;
    

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

     _currentAnimation = &_walkingDown;
}

Entity::~Entity() {}

unsigned Entity::getLevel() {
    return _level;
}
sf::FloatRect Entity::getLocalBounds() const {
    return _sprite.getLocalBounds();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_sprite, states);
}

sf::Texture Entity::getTexture() {
    return _texture;
}
sf::IntRect Entity::getIntRect() {
    return _intRect;
}

// All animation stuff

void Entity::setAnimation(const Animation& animation)
{
    m_animation = &animation;
    m_texture = m_animation->getSpriteSheet();
    m_currentFrame = 0;
    setFrame(m_currentFrame);
}

void Entity::setFrameTime(float time)
{
    _frameDelay = time;
}

void Entity::play()
{
    m_isPaused = false;
}

void Entity::play(const Animation& animation)
{
    if (getAnimation() != &animation)
        setAnimation(animation);
    play();
}

void Entity::pause()
{
    m_isPaused = true;
}

void Entity::stop()
{
    m_isPaused = true;
    m_currentFrame = 0;
    setFrame(m_currentFrame);
}

void Entity::setLooped(bool looped)
{
    m_isLooped = looped;
}

void Entity::setColor(const sf::Color& color)
{
    // Update the vertices' color
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}

const Animation* Entity::getAnimation() const
{
    return m_animation;
}

bool Entity::isLooped() const
{
    return m_isLooped;
}

bool Entity::isPlaying() const
{
    return !m_isPaused;
}

void Entity::setFrame(std::size_t newFrame, bool resetTime)
{
    if (m_animation)
    {
        //calculate new vertex positions and texture coordiantes
        sf::IntRect rect = m_animation->getFrame(newFrame);

        m_vertices[0].position = sf::Vector2f(0.f, 0.f);
        m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
        m_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

        float left = static_cast<float>(rect.left) + 0.0001f;
        float right = left + static_cast<float>(rect.width);
        float top = static_cast<float>(rect.top);
        float bottom = top + static_cast<float>(rect.height);

        m_vertices[0].texCoords = sf::Vector2f(left, top);
        m_vertices[1].texCoords = sf::Vector2f(left, bottom);
        m_vertices[2].texCoords = sf::Vector2f(right, bottom);
        m_vertices[3].texCoords = sf::Vector2f(right, top);
    }

    if (resetTime) {
        m_currentTime = 0.0f;
    }
}

void Entity::update(float deltaTime)
{
    std::cout << deltaTime << std::endl;
    if (!m_isPaused && m_animation)
    {
        _frameDelay += deltaTime;

        if (_frameDelay > 0.06f) {
            // get next Frame index
            if (m_currentFrame + 1 < m_animation->getSize())
                m_currentFrame++;
            else
            {
                // animation has ended
                m_currentFrame = 0; // reset to start

                if (!m_isLooped)
                {
                    m_isPaused = true;
                }

            }
        }

        // set the current frame, not reseting the time
        setFrame(m_currentFrame, false);
    }




 /*   // if not paused and we have a valid animation
    if (!m_isPaused && m_animation)
    {
        // add delta time
        m_currentTime += (deltaTime);

        // if current time is bigger then the frame time advance one frame
        if (m_frameTime == 0)
        {
            // reset time, but keep the remainder
           // m_currentTime = m_currentTime % m_frameTime;

            // get next Frame index
            if (m_currentFrame + 1 < m_animation->getSize())
                m_currentFrame++;
            else
            {
                // animation has ended
                m_currentFrame = 0; // reset to start

                if (!m_isLooped)
                {
                    m_isPaused = true;
                }

            }

            // set the current frame, not reseting the time
            setFrame(m_currentFrame, false);
        }
    }*/
}
