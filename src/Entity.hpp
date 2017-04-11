#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Object.hpp"

class Entity : public Object {
public:
    // Constructor
    Entity(std::string file_path, int sprite_format);
    virtual ~Entity();

    // Enum
    enum directions{UP, LEFT, DOWN, RIGHT};
    directions _facing;

    // Functions
    unsigned getLevel();
    sf::IntRect getIntRect();
    sf::FloatRect getLocalBounds() const override;


    // All animation stuff
    void update(float deltaTime);
    void setAnimation(const Animation& animation);
    void setFrameTime(float time);
    void play();
    void play(const Animation& animation);
    void pause();
    void stop();
    const Animation* getAnimation() const;
    bool isPlaying() const;
    void setFrame(std::size_t newFrame);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    // Variables
    int _level;
    int _spriteFormat;
    unsigned _health;
    std::string _name;

    // SFML variables
    sf::Sprite _sprite;
    sf::IntRect _intRect;
    sf::Texture _texture;

    // All animation stuff
    const Animation* _animation;
    const sf::Texture* _tempTexture;
    float _frameDelay;
    std::size_t _currentFrame;
    bool _isPaused;
    bool _isLooped;

    Animation _walkingUp;
    Animation _walkingLeft;
    Animation _walkingDown;
    Animation _walkingRight;
    Animation _standing;

    Animation* _currentAnimation;

    void loadAnimations();
};
