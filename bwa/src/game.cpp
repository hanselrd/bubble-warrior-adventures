#include "game.hpp"
#include "resource.hpp"
#include <string>
#include <utility>

constexpr const char* WINDOW_TITLE = "Bubble Warrior Adventures!";

bwa::Game::Game() {
	_lua.script_file("config.lua");
	sol::table resolution = _lua["resolution"];
	_font = Resource<sf::Font>::get(_lua["game_fonts"]["normal"]);
	_text.setFont(*_font);
	_text.setFillColor(sf::Color::Yellow);
	_text.setString("FPS:");
	auto xy = std::make_pair(
		resolution["x"].get<unsigned>(), 
		resolution["y"].get<unsigned>());
	if (_lua["fullscreen"].get<bool>())
		_window.create({ xy.first, xy.second }, WINDOW_TITLE,
			sf::Style::Fullscreen);
	else
		_window.create({ xy.first, xy.second }, WINDOW_TITLE);
	_window.setVerticalSyncEnabled(true);
	_gui.setWindow(_window);
}

void bwa::Game::run() {
	sf::Clock clock, update_fps;
	float last_time = 0.f, current_time, fps;
	bool show_fps_counter = _lua["show_fps_counter"];

	sf::CircleShape box;
	box.setRadius(16.f);
	box.setFillColor(sf::Color::Green);
	box.setPosition({ 100.f, 100.f });

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
		_window.draw(box);
		_gui.draw();
		// displays fps if show_fps_counter is true
		if (show_fps_counter)
			_window.draw(_text);
		_window.display();
	}
}
