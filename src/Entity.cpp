#include "Entity.hpp"

Entity::Entity(float radius, const sf::Color& color) {
    _body.setRadius(radius);
    _body.setFillColor(color);
}

Entity::~Entity() {}

sf::FloatRect Entity::getLocalBounds() const {
    return _body.getLocalBounds();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_body, states);
}
