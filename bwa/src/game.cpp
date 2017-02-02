#include <exception>
#include <string>
#include <utility>
#include "game.hpp"

constexpr const char* WINDOW_TITLE = "Bubble Warrior Adventures!";

bwa::Game::Game() {
	// Loads the config into the sol::state
	_lua.script_file("config.lua");
	// Converts the config's x and y resolution into a table
	sol::table resolution = _lua["resolution"];
	// Checks for font file and sets _font to it
	if (!_font.loadFromFile(_lua["game_fonts"]["normal"]))
	{
		throw std::invalid_argument(_FILE_NOT_FOUND_ERROR + _lua["game_fonts"]["normal"].get<std::string>());
	}
	_text.setFont(_font);
	_text.setFillColor(sf::Color::Yellow);
	_text.setString("FPS:");
	auto xy = std::make_pair(
		resolution["x"].get<unsigned>(), 
		resolution["y"].get<unsigned>());
	if (_lua["fullscreen"].get<bool>()) {
		_window.create({ xy.first, xy.second }, WINDOW_TITLE,
			sf::Style::Fullscreen);
	}
	else {
	_window.create({ xy.first, xy.second }, WINDOW_TITLE);
	_window.setVerticalSyncEnabled(true);
	_gui.setWindow(_window);
	}
}

void bwa::Game::run() {
	sf::Clock clock, update_fps;
	float last_time = 0.f, current_time, fps;
	bool show_fps_counter = _lua["show_fps_counter"];
	while (_window.isOpen()) {
		sf::Event e;
		while (_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_window.close();
			_gui.handleEvent(e);
		}
		// calculates fps
		if (show_fps_counter) {
			current_time = clock.restart().asSeconds();
			fps = 1.f / (current_time - last_time);
			if (update_fps.getElapsedTime() > sf::seconds(1.f)) {
				_text.setString("FPS: " + std::to_string(unsigned(fps)));
				update_fps.restart();
			}
		}
		_window.clear();
		_gui.draw();
		// displays fps if show_fps_counter is true
		if (show_fps_counter)
			_window.draw(_text);
		_window.display();
	}
}
