#include "game.hpp"
#include <iostream>
#include <utility>

constexpr const char* WINDOW_TITLE = "Bubble Warrior Adventures!";

bwa::Game::Game() {
	_lua.script_file("config.lua");
	sol::table resolution = _lua["resolution"];
	auto xy = std::make_pair(
		resolution["x"].get<unsigned>(), 
		resolution["y"].get<unsigned>());
	if (_lua["fullscreen"].get<bool>())
		_window.create({ xy.first, xy.second }, WINDOW_TITLE,
			sf::Style::Fullscreen);
	else
		_window.create({ xy.first, xy.second }, WINDOW_TITLE);
	_window.setVerticalSyncEnabled(true);
	std::cout << _lua["fonts_dir"].get<std::string>() << std::endl;
}

void bwa::Game::run() {
	while (_window.isOpen()) {
		sf::Event e;
		while (_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_window.close();
		}
		_window.clear();
		_window.display();
	}
}
