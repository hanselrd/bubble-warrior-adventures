#pragma once
#include <TGUI/TGUI.hpp>
#include <sol.hpp>
#include <memory>

namespace bwa {
	class Game final {
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		void run();

	private:
		std::shared_ptr<sf::Font> _font;
		sf::Text _text;
		sf::RenderWindow _window;
		tgui::Gui _gui;
		sol::state _lua;
	};
}
