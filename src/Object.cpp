#include "Object.hpp"

Object::Object() {
    //setting defaults
    //_name = "default";
    _isAttacking = false;
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

bool Object::checkCollision(const Object& first,const Object& second, sf::FloatRect& intersection) {
    if (first.getGlobalBounds().intersects(second.getGlobalBounds(), intersection))
    {
        return true;
    }
    else
        return false;
}

bool Object::isAttacking() const{
    return _isAttacking;
}
