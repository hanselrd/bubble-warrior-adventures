#include "Game.hpp" // relative header, check CONTRIBUTING.md
#include <string>
#include <utility>
#include "InitState.hpp"

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
	_stateHandler.pushState<InitState>(std::ref(_window), std::ref(_lua));
}

void bwa::Game::run() {
	// Create the clock and set up the FPS counter
	sf::Clock clock, updateFps;
	float lastTime = 0.f, currentTime, delta;
	bool showFpsCounter = _lua["config"]["showFpsCounter"];

	// Create FPS string iff showFpsCounter is true in the config
	if (showFpsCounter) {
		auto lblFps = std::make_shared<tgui::Label>();
		lblFps->setTextColor(sf::Color::Yellow);
		lblFps->setTextSize(30);
		_gui.add(lblFps, "lblFps");
	}

	// Normal window event loop
	while (_window.isOpen()) {
		_stateHandler.handleTransitions();

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

		// Update FPS string iff showFpsCounter is true
		if (showFpsCounter) {
			if (updateFps.getElapsedTime() > sf::seconds(1.f)) {
				auto lblFps = _gui.get<tgui::Label>("lblFps");
				lblFps->setText(std::to_string(unsigned(1.f / delta)));
				updateFps.restart();
			}
		}
    
		// Clear and render to the window
		_window.clear();
		_stateHandler.draw(_window);
		_gui.draw();
		_window.display();
	}
}
