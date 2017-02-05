#include "FriendlyEntity.hpp"

bwa::FriendlyEntity::FriendlyEntity() {

}
bwa::FriendlyEntity::FriendlyEntity(sf::Texture &texture, sf::IntRect &texture_rect) {
	_texture = texture;
	_sprite.setTexture(texture);
	_sprite.setTextureRect(texture_rect);
}

void bwa::FriendlyEntity::animateLeft()
{
	if (_clock.getElapsedTime().asSeconds() > 0.1f) {
		// If the sprite isnt facing up, make it face up
		if (_sprite.getTextureRect().top != (64 * 9))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left, (64 * 9));
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is at the end of the "loop", reset it
		if (_sprite.getTextureRect().left == (64 * 8))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i((64 * 1), _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is somewhere in the loop, progress it
		else {
			sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		_clock.restart();
	}
	_sprite.move(-2, 0);
}

void bwa::FriendlyEntity::animateRight()
{
	if (_clock.getElapsedTime().asSeconds() > 0.1f) {
		// If the sprite isnt facing right, make it face right
		if (_sprite.getTextureRect().top != (64 * 11))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left, (64 * 11));
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is at the end of the "loop", reset it
		if (_sprite.getTextureRect().left == (64 * 8))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i((64 * 1), _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is somewhere in the loop, progress it
		else {
			sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		_clock.restart();
	}
	_sprite.move(2, 0);
}

void bwa::FriendlyEntity::animateUp()
{
	if (_clock.getElapsedTime().asSeconds() > 0.1f) {
		// If the sprite isnt facing up, make it face up
		if (_sprite.getTextureRect().top != (64 * 8))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left, (64 * 8));
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is at the end of the "loop", reset it
		if (_sprite.getTextureRect().left == (64 * 8))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i((64 * 1), _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is somewhere in the loop, progress it
		else {
			sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		_clock.restart();
	}
	_sprite.move(0, -2);
}

void bwa::FriendlyEntity::animateDown()
{
	if (_clock.getElapsedTime().asSeconds() > 0.1f) {
		// If the sprite isnt facing down, make it face down
		if (_sprite.getTextureRect().top != (64 * 10))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i(0, (64 * 10));
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is at the end of the "loop", reset it
		if (_sprite.getTextureRect().left == ((64 * 1) * 8))
		{
			sf::Vector2i new_rect_coords = sf::Vector2i((64 * 1), _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		// If the sprite is somewhere in the loop, progress it
		else {
			sf::Vector2i new_rect_coords = sf::Vector2i(_sprite.getTextureRect().left + 64, _sprite.getTextureRect().top);
			sf::Vector2i new_rect_dimensions = sf::Vector2i(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
			_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
		}
		_clock.restart();
	}
	_sprite.move(0, 2);
}

void bwa::FriendlyEntity::setPosition(float x, float y)
{
	_sprite.setPosition(x,y);
}

void bwa::FriendlyEntity::draw(sf::RenderWindow &window) {
	window.draw(_sprite);
}