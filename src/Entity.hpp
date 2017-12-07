#pragma once
#include <cereal/cereal.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.hpp"
#include "Object.hpp"

class Entity : public Object {
protected:
    sf::CircleShape _circle;
    unsigned _level;
    unsigned _health;
    unsigned _spriteFormat;
    sf::Vector2f _velocity;
    sf::Texture _texture;
    sf::Sprite _sprite;

    const Animation* _animation;
    Animation _attackUp;
    Animation _attackLeft;
    Animation _attackDown;
    Animation _attackRight;
    void generateWalkAnimations(int spriteFormat);
    void generateAttackAnimations(int spriteFormat);
    
    // Loading animation parsing   
    friend class cereal::access;
    template <class Archive>
    void save(Archive& ar) const;
    template <class Archive>
    void load(Archive& ar);

    const sf::Texture* _tempTexture;
    float _frameDelay;
    sf::IntRect _intRect;
    std::size_t _currentFrame;
    std::string _fileName;
    bool _isPaused, _isLooped, _isAttacking;
    Animation _walkingUp, _walkingLeft, _walkingDown, _walkingRight, _standing;
    Animation* _currentAnimation;

    enum class EntityType { Object, Item, Player, Enemy, NPC };
    EntityType _entityType;

public:
    enum class Direction { Up, Left, Down, Right } _direction;
    Entity::Direction getDirection();


    Entity(const std::string& filePath, int spriteFormat);
    Entity();
    ~Entity();
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
};
