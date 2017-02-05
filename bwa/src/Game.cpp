#include "Game.hpp" // relative header
#include <stdexcept>
#include <string>
#include <utility>
#include "MainMenu.hpp"
#include "ResourceLoader.hpp"
#include "TitleScreen.hpp"

#include "test.hpp"

constexpr const char* WINDOW_TITLE = "Bubble Warrior Adventures!";

bwa::Game::Game() {
	// Loads the ability to require modules in lua
	_lua.open_libraries(sol::lib::base, 
		sol::lib::package, 
		sol::lib::table,
		sol::lib::string);

	// Loads the 'utility' module into lua
	_lua.require_file("utility", "scripts/utility.lua");

	// Loads the config into the sol::state
	_lua.require_file("config", "config.lua");

	// Converts the config's x and y resolution into a table
	sol::table resolution = _lua["config"]["resolution"];

	// Gets the fonts and sprites tables from assets table
	sol::table assets = _lua["config"]["assets"];
	sol::table fonts = assets["fonts"];
	sol::table sprites = assets["sprites"];

	// Auto loading
	for (const auto& font : fonts)
		ResourceLoader<sf::Font>::load(font.second.as<std::string>());

	for (const auto& sprite : sprites)
		ResourceLoader<sf::Texture>::load(sprite.second.as<std::string>());

	// Gets font from resource loader and binds it to _text
	auto font = ResourceLoader<sf::Font>::get(_lua["config"]["assets"]["fonts"][1]);
	_text.setFont(*font);
	_text.setFillColor(sf::Color::Yellow);
	_text.setString("FPS:");

	// Pull the x and y window resolution coordinates from the config
	auto xy = std::make_pair(
		resolution["x"].get<unsigned>(), 
		resolution["y"].get<unsigned>());

	// Create a fullscreen window if set to true in config, windowed if false.
	if (_lua["config"]["fullscreen"].get<bool>())
		_window.create({ xy.first, xy.second }, 
			WINDOW_TITLE,
			sf::Style::Fullscreen);
	else
		_window.create({ xy.first, xy.second }, WINDOW_TITLE);

	// Lock FPS to monitor's refresh rate and binds _window to _gui
	_window.setVerticalSyncEnabled(true);
	_gui.setWindow(_window);

	// Creates the initial GameState on the stack to be MainMenu
	_states.push(std::make_unique<test>(std::ref(_window)));
}

void bwa::Game::run() {
	// Create the clock and set it up for the FPS counter
	sf::Clock clock, update_fps;
	float last_time = 0.f, current_time, fps;
	bool show_fps_counter = _lua["config"]["show_fps_counter"];

	// Normal window event loop
	while (_window.isOpen()) {
		sf::Event e;
		while (_window.pollEvent(e)) {
			
			//If the user hits the x or presses Esc, close the window
			if (e.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					_window.close();
				}
			_states.top()->handleEvents(e);
			_states.top()->update(fps);
		}

		// Calculates fps
		if (show_fps_counter) {
			current_time = clock.restart().asSeconds();
			fps = 1.f / (current_time - last_time);
			if (update_fps.getElapsedTime() > sf::seconds(1.f)) {
				_text.setString("FPS: " + std::to_string(unsigned(fps)));
				update_fps.restart();
			}
		}
    
		_window.clear();
		_states.top()->draw(_window);
		_gui.draw();

		// Displays FPS if show_fps_counter is true
		if (show_fps_counter)
			_window.draw(_text);
		_window.display();

	} // End normal window event loop
}
