#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.hpp"
#include "Object.hpp"

class Entity : public Object {
public:
    explicit Entity(const std::string& filePath, unsigned spriteFormat);
    explicit Entity(float radius, const sf::Color& color);
    virtual ~Entity();
    sf::FloatRect getLocalBounds() const override;
    void update(float delta);
    void setAnimation(const Animation& animation);
    void setFrameTime(float time);
    void play();
    void play(const Animation& animation);
    void pause();
    void stop();
    const Animation* getAnimation() const;
    bool isPlaying() const;
    void setFrame(std::size_t n);
    unsigned getLevel() const;
    unsigned getHealth() const;
    sf::Vector2f getVelocity() const;
    void setHealth(unsigned val);
    void setLevel(unsigned val);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    enum class Direction { Up, Left, Down, Right } _direction;
    sf::CircleShape _circle;
    unsigned _level;
    unsigned _health;
    unsigned _spriteFormat;
    sf::Vector2f _velocity;
    sf::Texture _texture;
    sf::Sprite _sprite;
    const Animation* _animation;
    const sf::Texture* _tempTexture;
    float _frameDelay;
    sf::IntRect _intRect;
    std::size_t _currentFrame;
    bool _isPaused, _isLooped;
    Animation _walkingUp, _walkingLeft, _walkingDown, _walkingRight, _standing;
    Animation* _currentAnimation;
};
