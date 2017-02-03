#pragma once
#include <SFML/Window.hpp>

namespace bwa {
	class GameState {
	public:
		virtual void draw(sf::Window &window) = 0;
		virtual void handleEvents(sf::Event &e) = 0;
		virtual void update() = 0;

	protected:
	};
}