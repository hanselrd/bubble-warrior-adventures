#pragma once
#include <SFML/Graphics.hpp>

class Object : public sf::Drawable, public sf::Transformable {
public:
    virtual ~Object();
    virtual sf::FloatRect getLocalBounds() const = 0;
    sf::FloatRect getGlobalBounds() const;
    static bool checkCollision(const Object& first, const Object& second, sf::FloatRect& intersection);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
