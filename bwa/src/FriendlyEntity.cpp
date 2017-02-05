#include "FriendlyEntity.hpp"

bwa::FriendlyEntity::FriendlyEntity(sf::Texture &texture) {
	_texture = texture;
	_sprite.setTexture(texture);
}

void bwa::FriendlyEntity::animateLeft()
{
}

void bwa::FriendlyEntity::animateRight()
{
}

void bwa::FriendlyEntity::animateUp()
{
}

void bwa::FriendlyEntity::animateDown()
{
}

void bwa::FriendlyEntity::draw(sf::RenderWindow &window) {
	window.draw(_sprite);
}