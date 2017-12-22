#include "InvisibleBarrier.hpp"
#include "Object.hpp"

InvisibleBarrier::InvisibleBarrier(Map::Object mapObject) 
    : Object() {

    _isAttacking = false;
    setPosition(mapObject.getPosition());
    setOrigin(mapObject.getRect().width/2.0f, mapObject.getRect().height/2.0f);
    _entityType = EntityType::Object;
    _name = "collideable";
}

sf::FloatRect InvisibleBarrier::getLocalBounds() const {
    return sf::FloatRect();
}

void InvisibleBarrier::draw(sf::RenderTarget& target, sf::RenderStates states) const {
}