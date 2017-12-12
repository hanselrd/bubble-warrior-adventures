#pragma once
#include <SFML/Graphics.hpp>

class Object : public sf::Drawable, public sf::Transformable {
public:
    Object();
    virtual ~Object();
    virtual sf::FloatRect getLocalBounds() const = 0;
    sf::FloatRect getGlobalBounds() const;
    static bool checkCollision(const Object& first,const Object& second, sf::FloatRect& intersection);
    enum class EntityType { Object, Item, Player, Enemy, NPC };
    EntityType _entityType;

    const EntityType getEntityType() const;

    std::string _name, _filePath;
protected:

    bool _isAttacking;
    bool isAttacking() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
