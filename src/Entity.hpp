#pragma once
#include <SFML/Graphics.hpp>
#include "Object.hpp"

class Entity : public Object {
public:
    Entity(std::string file_path, int sprite_format);
    virtual ~Entity();
    sf::FloatRect getLocalBounds() const override;

    unsigned getLevel();
    enum directions{UP, LEFT, DOWN, RIGHT};

    directions _facing;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:

    int _level;
    int _spriteFormat;
    sf::Sprite _sprite;
    sf::Texture _texture;
    unsigned _health;
};
