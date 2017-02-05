#include "FriendlyEntity.hpp"
#include "ResourceLoader.hpp"
#include "test.hpp"

bwa::test::test(sf::RenderWindow &window) {
	heroRect = sf::IntRect(0, (64 * 8), (64), (64));
	texture.loadFromFile("assets/sprites/golden_hero_female_no_shield_no_hat.png");
	heroSprite = sf::Sprite(texture, heroRect);
	heroSprite.setPosition(400, 400);
}
void bwa::test::draw(sf::RenderWindow &window) {
	window.clear();
	if (clock2.getElapsedTime().asSeconds() > 0.1f) {
		if (heroRect.left == ((64 * 1) * 8))
			heroRect.left = 0;
		else heroRect.left += (64 * 1);
		heroSprite.setTextureRect(heroRect);
		clock2.restart();
	}
	heroRect.top = (64 * 9);
	heroSprite.move(-1, 0);
	window.draw(heroSprite);
}

void bwa::test::handleEvents(sf::Event & e)
{
}

void bwa::test::update(float delta)
{
}

