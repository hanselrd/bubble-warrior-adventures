#pragma once
#include <SFML/Graphics.hpp>

class Object : public sf::Drawable, public sf::Transformable {
public:
    virtual ~Object();
    virtual sf::FloatRect getLocalBounds() const = 0;
    sf::FloatRect getGlobalBounds() const;
    static bool checkCollision(Object& first, Object& second, sf::FloatRect& intersection);

protected:
    enum class EntityType { Object, Item, Player, Enemy, NPC };
    EntityType _entityType;

    bool _isAttacking;
    bool isAttacking();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    bool intersects(const Object& first, const Object& second, sf::FloatRect& intersection) const;
};
