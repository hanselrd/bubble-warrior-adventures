#include "Game.hpp"
#include <pybind11/eval.h>
namespace py = pybind11;
#include <string>
#include <utility>
#include "ResourceCache.hpp"
#include "TitleScreen.hpp"

constexpr const char* WINDOW_TITLE = "Bubble Warrior Adventures!";

Game::Game() {
	// Initialize Python interpreter
	Py_Initialize();

	// Create global scope and load config script
	auto pyGlobal = ResourceCache<py::dict>::create("global");
	*pyGlobal = py::dict(py::module::import("__main__").attr("__dict__"));
	py::eval_file("config.py", *pyGlobal);

	// Load the resolution dict from config
	auto resolution = (*pyGlobal)["config"]["resolution"].cast<py::dict>();

	// Pull the x and y window resolution coordinates from the config
	auto xy = std::make_pair(
		resolution["x"].cast<unsigned>(), 
		resolution["y"].cast<unsigned>());

	// Create a fullscreen window if set to true in config, windowed if false.
	if ((*pyGlobal)["config"]["fullscreen"].cast<bool>())
		_window.create({ xy.first, xy.second }, 
			WINDOW_TITLE,
			sf::Style::Fullscreen);
	else
		_window.create({ xy.first, xy.second }, WINDOW_TITLE);

	// Lock FPS to monitor's refresh rate and binds _window to _gui
	_window.setVerticalSyncEnabled(true);
	_gui.setWindow(_window);

	// Loads the default GUI theme
	ResourceCache<tgui::Theme>::create("default", (*pyGlobal)["config"]["theme"].cast<std::string>());

	// Sets initial state
	_stateHandler.change<TitleScreen>(std::ref(_window));
}

void Game::run() {
	// Gets the global python scope from ResourceCache
	auto pyGlobal = ResourceCache<py::dict>::get("global");

	// Create the clock and set up the FPS counter
	sf::Clock clock, updateFps;
	float lastTime = 0.f, currentTime, delta;
	bool showFpsCounter = (*pyGlobal)["config"]["showFpsCounter"].cast<bool>();

	// Create FPS string iff showFpsCounter is true in the config
	if (showFpsCounter) {
		auto theme = ResourceCache<tgui::Theme>::get("default");
		tgui::Label::Ptr lblFps = theme->load("Label");
		lblFps->setTextColor(sf::Color::Yellow);
		lblFps->setTextSize(30);
		_gui.add(lblFps, "lblFps");
	}

	// Normal window event loop
	while (_window.isOpen()) {
		_stateHandler.handleTransition();

		// Handle window events and delegate them to individual states
		sf::Event e;
		while (_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_window.close();
			_stateHandler.handleEvent(e);
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
