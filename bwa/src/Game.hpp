#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sol.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>
#include <string>
#include <stack>
#include "GameState.hpp"

namespace bwa {
	class Game final {
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		void run();

	private:
		sf::RenderWindow _window;
		sf::Text _text;
		sf::RenderWindow _window;
		tgui::Gui _gui;
		sol::state _lua;
		std::stack<std::unique_ptr<GameState>> _states;
	};
}
