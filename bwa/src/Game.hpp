#pragma once
#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>
#include <string>
#include "StateHandler.hpp"

namespace bwa {
	class Game final {
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		void run();

	private:
		sf::RenderWindow _window;
		sol::state _lua;
		tgui::Gui _gui;
		StateHandler _stateHandler;
	};
}