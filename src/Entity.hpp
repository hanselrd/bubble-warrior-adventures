#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Object.hpp"

class Entity : public Object {
public:
    Entity(std::string file_path, int sprite_format);
    virtual ~Entity();
    sf::FloatRect getLocalBounds() const override;

    unsigned getLevel();
    sf::Texture getTexture();
    sf::IntRect getIntRect();
    enum directions{UP, LEFT, DOWN, RIGHT};

    directions _facing;

    // All animation stuff
    void update(float deltaTime);
    void setAnimation(const Animation& animation);
    void setFrameTime(float time);
    void play();
    void play(const Animation& animation);
    void pause();
    void stop();
    void setLooped(bool looped);
    void setColor(const sf::Color& color);
    const Animation* getAnimation() const;
    bool isLooped() const;
    bool isPlaying() const;
    sf::Time getFrameTime() const;
    void setFrame(std::size_t newFrame, bool resetTime = true);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    int _level;
    int _spriteFormat;
    unsigned _health;

    sf::Clock _animationClock;
    sf::Sprite _sprite;
    sf::IntRect _intRect;
    sf::Texture _texture;

    // All animation stuff
    const Animation* m_animation;
    float _frameDelay;
    float m_currentTime;
    std::size_t m_currentFrame;
    bool m_isPaused;
    bool m_isLooped;
    const sf::Texture* m_texture;
    sf::Vertex m_vertices[4];

    Animation _walkingUp;
    Animation _walkingLeft;
    Animation _walkingDown;
    Animation _walkingRight;

    Animation* _currentAnimation;

};
