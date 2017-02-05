#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "FriendlyEntity.hpp"

/*
	Empty constuctor. Sets default values for error
	prevention.
*/
bwa::FriendlyEntity::FriendlyEntity() {
	_health = 1;
	_damage = 1;
	_invincible = true;
	_x_coordinate = 0;
	_y_coordinate = 0;
}

/*
	Main constructor to use to generate an entity.
	texture_rect sets the initial tileset location
	based on the texture file.
*/
bwa::FriendlyEntity::FriendlyEntity(sf::Texture &texture, sf::IntRect &texture_rect) {
	_health = 1;
	_damage = 1;
	_invincible = true;
	_texture = texture;
	_sprite.setTexture(texture);
	_sprite.setTextureRect(texture_rect);
}

/*
	(Left entity movement)
	This function takes the coordinates of the sprite's
	current location on the texture files (.png), and 
	changes it to the next coordinates, and also moves the sprite.
*/
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

	// Move the sprite to the left
	_x_coordinate -= 2;
}

/*
	(Right entity movement)
	This function takes the coordinates of the sprite's
	current location on the texture files (.png), and
	changes it to the next coordinates, and also moves the sprite.
*/
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

	// Move the sprite to the right
	_x_coordinate += 2;
}

/*
	(Forward entity movement)
	This function takes the coordinates of the sprite's
	current location on the texture files (.png), and
	changes it to the next coordinates, and also moves the sprite.
*/
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

	// Move the sprite upwards
	_y_coordinate -= 2;
}

/*
	(Downward entity movement)
	This function takes the coordinates of the sprite's
	current location on the texture files (.png), and
	changes it to the next coordinates, and also moves the sprite.
*/
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
	// Move the sprite 2 pixels down
	_y_coordinate += 2;
}

/*
	This function takes the coordinates of the sprite's
	current location on the texture files (.png), and
	changes it to the "sprite standing" coordinates of the 
	direction the sprite was last facing.
*/
void bwa::FriendlyEntity::animateStanding() {
	// Stores the bounds of the current sprite from the texture
	sf::IntRect current_sprite = _sprite.getTextureRect();

	if (current_sprite.top == (64 * 8)) {
		sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
		sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
		_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
	}
	else if (current_sprite.top == (64 * 9)) {
		sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
		sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
		_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
	}
	else if (current_sprite.top == (64 * 10)) {
		sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
		sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
		_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
	}
	else if (current_sprite.top == (64 * 11)) {
		sf::Vector2i new_rect_coords = sf::Vector2i(0, current_sprite.top);
		sf::Vector2i new_rect_dimensions = sf::Vector2i(current_sprite.width, current_sprite.height);
		_sprite.setTextureRect(sf::IntRect(new_rect_coords, new_rect_dimensions));
	}
}

/*
	This function sets the entity's internal coordinates
	to the given location.
*/
void bwa::FriendlyEntity::setPosition(float x, float y)
{
	_x_coordinate = x;
	_y_coordinate = y;
}

/*
	Draws the entity's sprite to the window using
	the internal coordinates to place the sprite.
*/
void bwa::FriendlyEntity::draw(sf::RenderWindow &window) {
	_sprite.setPosition(_x_coordinate, _y_coordinate);
	window.draw(_sprite);
}