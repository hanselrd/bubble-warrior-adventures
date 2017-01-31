#pragma once
#include <SFML/Graphics.hpp>
#include <sol.hpp>

namespace bwa {
	class Game final {
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		void run();

	private:
		sf::Font _font;
		sf::Text _text;
		sf::RenderWindow _window;
		sol::state _lua;
	};
}
