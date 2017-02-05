#pragma once
#include <SFML/Window.hpp>
#include "GameState.hpp"
#include "FriendlyEntity.hpp"

namespace bwa {
	class test : public GameState {
	public:
		test(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
		void handleEvents(sf::Event &e);
		void update(float delta);

		bwa::FriendlyEntity _player;
		sf::Texture texture;
		sf::IntRect heroRect;
	};
}