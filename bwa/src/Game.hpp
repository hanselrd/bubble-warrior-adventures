#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>
#include <string>
#include "StateHandler.hpp"

class Game final {
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void run();

private:
	sf::RenderWindow _window;
	tgui::Gui _gui;
	StateHandler _stateHandler;
};
