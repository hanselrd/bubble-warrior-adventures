#pragma once
#include <SFML/Graphics.hpp>

namespace bwa {
	class GameState {
	public:
		virtual void draw(sf::RenderWindow &window) = 0;
		virtual void handleEvents(sf::Event &e) = 0;
		virtual void update(float delta) = 0;
	};
}