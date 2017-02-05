#pragma once
#include "GameState.hpp"
#include <SFML/Window.hpp>

namespace bwa {
	class test : public GameState {
	public:
		test(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
		void handleEvents(sf::Event &e);
		void update(float delta);

		sf::Clock clock2;
		sf::Texture texture;
		sf::Sprite heroSprite;
		sf::IntRect heroRect;
	};
}