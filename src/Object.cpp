#include "Object.hpp"

Object::~Object() {}

sf::FloatRect Object::getGlobalBounds() const {
    //return getTransform().transformRect(getLocalBounds());
    return getTransform().transformRect(getLocalBounds());
}
//bool Object::intersects(const Object& second, sf::FloatRect& intersection) const {
//    sf::FloatRect secondRect = second.getGlobalBounds();
//    if (getGlobalBounds().intersects(secondRect)) {
//        return true;
//    }
//    else {
//        return false;
//    }
//}
bool Object::checkCollision(const Object& first, const Object& second, sf::FloatRect& intersection) {
    if (first.getGlobalBounds().intersects(second.getGlobalBounds(), intersection))
        return true;
    else
        return false;
}
