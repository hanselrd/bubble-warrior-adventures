#pragma once
#include "GameState.hpp"
#include "FriendlyEntity.hpp"
#include <SFML/Window.hpp>

namespace bwa {
	class test : public GameState {
	public:
		test(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
		void handleEvents(sf::Event &e);
		void update(float delta);

		bwa::FriendlyEntity _entity;
		sf::Texture texture;
		sf::IntRect heroRect;
	};
}