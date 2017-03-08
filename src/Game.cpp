#include "Game.hpp"
#include <pybind11/eval.h>
namespace py = pybind11;
#include <string>
#include "Config.hpp"
#include "Locator.hpp"
#include "ResourceCache.hpp"
#include "Settings.hpp"
#include "TitleScreen.hpp"
#include "Tmx.hpp"

namespace game {
    PYBIND11_PLUGIN(game) {
        py::module m("game", "Game module");

        initSettings(m);
        m.attr("settings") = Locator<Settings>::get();

        auto m_sf = m.def_submodule("sf", "SFML module");
        py::class_<sf::IntRect>(m_sf, "IntRect")
            .def(py::init<>())
            .def_readwrite("x", &sf::IntRect::left)
            .def_readwrite("y", &sf::IntRect::top)
            .def_readwrite("w", &sf::IntRect::width)
            .def_readwrite("h", &sf::IntRect::height);

        py::class_<sf::Transformable>(m_sf, "Transformable")
            .def(py::init<>())
            .def_property_readonly("pos", &sf::Transformable::getPosition);

        py::class_<sf::Vector2f>(m_sf, "Vector2f")
            .def(py::init<>())
            .def_readwrite("x", &sf::Vector2f::x)
            .def_readwrite("y", &sf::Vector2f::y);

        initTmx(m);

        return m.ptr();
    }
}

Game::Game() {
    // Initialize Python interpreter
    PyImport_AppendInittab("game", &game::pybind11_init);
    Py_Initialize();

    // Check if settings.json exists and overwrite default settings
    Locator<Settings>::provide(new Settings("settings.json"));
    auto settings = Locator<Settings>::get();

    // Get the resolution from settings
    auto resolution = settings->getResolution();

    // Create a fullscreen window if set to true in settings, windowed if false.
    if (settings->getFullscreen())
        _window.create({ std::get<0>(resolution), std::get<1>(resolution) }, WINDOW_TITLE, sf::Style::Fullscreen);
    else
        _window.create({ std::get<0>(resolution), std::get<1>(resolution) }, WINDOW_TITLE);

    // Lock FPS to monitor's refresh rate and binds _window to _gui
    _window.setVerticalSyncEnabled(true);
    _gui.setWindow(_window);

    // Loads the default GUI theme
    ResourceCache<tgui::Theme>::create("default", THEMES_DIR + settings->getTheme());

    // Sets initial state
    _stateHandler.change<TitleScreen>(std::ref(_window));
}

Game::~Game() {
    // Destroy the Python interpreter
    Py_Finalize();
}

void Game::run() {
    // Locates and gets the Settings object
    auto settings = Locator<Settings>::get();

    // Create the clock
    sf::Clock clock, updateFps;
    float lastTime = 0.f, currentTime, delta;

    // Create FPS string iff showFpsCounter is true in the settings
    if (settings->getShowFpsCounter()) {
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
        if (settings->getShowFpsCounter()) {
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
