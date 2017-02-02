#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sol.hpp>
#include <string>
#include <TGUI/TGUI.hpp>

namespace bwa {
	class Game final {
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		void run();
		const std::string _FILE_NOT_FOUND_ERROR = "**File not found, please find: ";

	private:
		sf::Font _font;
		sf::Text _text;
		sf::RenderWindow _window;
		tgui::Gui _gui;
		sol::state _lua;
	};
}
