#include "Entity.hpp"

Entity::Entity(std::string file_path, int sprite_format) {
    _texture.loadFromFile("assets/sprites/" + file_path);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, (64 * 10), sprite_format, sprite_format));
    _spriteFormat = sprite_format;
    _level = 1;
}

Entity::~Entity() {}

unsigned Entity::getLevel() {
    return _level;
}
sf::FloatRect Entity::getLocalBounds() const {
    return _sprite.getLocalBounds();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_sprite, states);
}
