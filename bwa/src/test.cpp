#include "FriendlyEntity.hpp"
#include "ResourceLoader.hpp"
#include "test.hpp"

bwa::test::test(sf::RenderWindow &window) {
	texture.loadFromFile("assets/sprites/golden_hero_male_no_shield_no_hat.png");

	sf::IntRect entityRect = sf::IntRect(0, (64 * 8), (64), (64));

	_entity = FriendlyEntity(texture, entityRect);
	_entity.setPosition(window.getSize().x/2, window.getSize().y/2);
}
void bwa::test::draw(sf::RenderWindow &window) {
	window.clear();
	_entity.draw(window);
}

void bwa::test::handleEvents(sf::Event & e)
{
	if (e.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			_entity.animateUp();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_entity.animateDown();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			_entity.animateLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			_entity.animateRight();
		}

	}
}

void bwa::test::update(float delta)
{
}

