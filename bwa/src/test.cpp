#include "FriendlyEntity.hpp"
#include "ResourceLoader.hpp"
#include "test.hpp"

/*
	This class takes place of a gamestate where the main game
	would be played. Used to test animations and user key input.
*/
bwa::test::test(sf::RenderWindow &window) {
	// Change this to use resource loader
	texture.loadFromFile("assets/sprites/golden_hero_male_no_shield_no_hat.png");
	// Change this to use resource loader?
	// The sprite's frame from the texture
	sf::IntRect entityRect = sf::IntRect(0, (64 * 8), (64), (64));

	// Creates a player entity for this "window" gamestate
	_player = FriendlyEntity(texture, entityRect);
	// Sets the position here (will be changed later)
	_player.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f);
}

void bwa::test::draw(sf::RenderWindow &window) {
	window.clear();
	_player.draw(window);
}

void bwa::test::handleEvents(sf::Event & e)
{
	if (e.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			_player.animateUp();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_player.animateDown();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			_player.animateLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			_player.animateRight();
		}
	}
	else if (e.type == sf::Event::KeyReleased) {
		_player.animateStanding();
	}
}

void bwa::test::update(float delta)
{
}

