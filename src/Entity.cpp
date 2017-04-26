#include "Entity.hpp"

Entity::Entity(float radius, const sf::Color& color) {
    _circle.setRadius(radius);
    _circle.setFillColor(color);
}

Entity::~Entity() {}

sf::FloatRect Entity::getLocalBounds() const {
    return _circle.getLocalBounds();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_circle, states);
}
