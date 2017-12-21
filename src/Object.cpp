#include "Object.hpp"

Object::Object() {
    //setting defaults
    //_name = "default";
    _isAttacking = false;
    _filePath = "default";
    if (_entityType != EntityType::Enemy ||
        _entityType != EntityType::Item ||
        _entityType != EntityType::NPC ||
        _entityType != EntityType::Player) {
        _entityType = EntityType::Object;
    }
    
}
Object::~Object() {}

sf::FloatRect Object::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}

const Object::EntityType Object::getEntityType() const {
    return _entityType;
}

bool Object::checkCollision(const Object& first,const Object& second, sf::FloatRect& intersection) {
    
    // Insert code here to check attacking status to fix
    // Issues with damage dealing
    //*******************************************************
    if (first.getGlobalBounds().intersects(second.getGlobalBounds(), intersection)
        && second.getEntityType() != EntityType::Spawn
        && intersection.width > 10)
    {
        return true;
    }
    else
        return false;
}

bool Object::isAttacking() const{
    return _isAttacking;
}