#include "Game.hpp" // relative header, check CONTRIBUTING.md
#include <stdexcept>
#include <string>
#include <utility>
#include "InitState.hpp"
#include "ResourceLoader.hpp"

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
	// auto font = ResourceLoader<sf::Font>::get(_lua["config"]["assets"]["fonts"][1]);
	// _text.setFont(*font);
	// _text.setFillColor(sf::Color::Yellow);
	// _text.setString("FPS:");
	auto lblFps = std::make_shared<tgui::Label>();
	lblFps->setText("FPS:");
	lblFps->setTextColor(sf::Color::Yellow);
	_gui.add(lblFps, "lblFps");

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

	// Sets initial state
	_stateHandler.pushState<InitState>(std::ref(_window));
}

void bwa::Game::run() {
	// Create the clock and set it up for the FPS counter
	sf::Clock clock, updateFps;
	float lastTime = 0.f, currentTime, delta;
	bool showFpsCounter = _lua["config"]["show_fps_counter"];

	// Normal window event loop
	while (_window.isOpen()) {
		sf::Event e;
		while (_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_window.close();
			_stateHandler.handleEvents(e);
			_gui.handleEvent(e);
		}

		// Calculate delta and pass to current state's update
		currentTime = clock.restart().asSeconds();
		delta = currentTime - lastTime;
		_stateHandler.update(delta);

		// Calculates fps
		if (showFpsCounter) {
			if (updateFps.getElapsedTime() > sf::seconds(1.f)) {
				auto lblFps = _gui.get<tgui::Label>("lblFps");
				lblFps->setText("FPS: " + std::to_string(unsigned(1.f / delta)));
				updateFps.restart();
			}
		}
    
		_window.clear();
		_stateHandler.draw(_window);
		_gui.draw();

		_window.display();
	}
}
