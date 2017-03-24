#pragma once
#include <SFML/Graphics.hpp>
#include "Object.hpp"

class Entity : public Object {
public:
    explicit Entity(float radius, const sf::Color& color);
    virtual ~Entity();
    sf::FloatRect getLocalBounds() const override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    sf::CircleShape _body;
    unsigned _health, _mana;
};
