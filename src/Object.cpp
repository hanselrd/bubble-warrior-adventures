#include "Object.hpp"

Object::~Object() {}

sf::FloatRect Object::getGlobalBounds() const {
    //return getTransform().transformRect(getLocalBounds());
    return getTransform().transformRect(getLocalBounds());
}

bool Object::checkCollision(Object& first, Object& second, sf::FloatRect& intersection) {
    if (first.getGlobalBounds().intersects(second.getGlobalBounds(), intersection))
        return true;
    else
        return false;
}

bool Object::isAttacking() {
    return _isAttacking;
}
