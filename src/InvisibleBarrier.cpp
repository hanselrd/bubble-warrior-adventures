#include "InvisibleBarrier.hpp"

InvisibleBarrier::InvisibleBarrier(Map::Object mapObject) 
    : Object() {

    _isAttacking = false;
    setPosition(mapObject.getPosition());
    _entityType = EntityType::Object;
}

//sf::FloatRect InvisibleBarrier::getLocalBounds() const {
//    return sf::FloatRect(getPosition(), )
//}