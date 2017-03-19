#include "Game.hpp"
#include <pybind11/pybind11.h>
namespace py = pybind11;
#include <string>
#include "Config.hpp"
#include "Locator.hpp"
#include "Map.hpp"
#include "TitleScreen.hpp"

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

        initMap(m);

        return m.ptr();
    }
}

Game::Game() {
    PyImport_AppendInittab("game", &game::pybind11_init);
    Py_Initialize();

    _resourceHandler = std::make_shared<ResourceHandler>();
    _settings = std::make_shared<Settings>("settings.json");
    _stateHandler = std::make_shared<StateHandler>();

    Locator<ResourceHandler>::provide(_resourceHandler);
    Locator<Settings>::provide(_settings);
    Locator<StateHandler>::provide(_stateHandler);

    auto resolution = _settings->getResolution();

    if (_settings->getFullscreen())
        _window.create({ std::get<0>(resolution), std::get<1>(resolution) }, WINDOW_TITLE, sf::Style::Fullscreen);
    else
        _window.create({ std::get<0>(resolution), std::get<1>(resolution) }, WINDOW_TITLE);

    _window.setVerticalSyncEnabled(true);
    _gui.setWindow(_window);

    _resourceHandler->emplace<tgui::Theme>("default", THEMES_DIR + _settings->getTheme());

    _stateHandler->change<TitleScreen>(std::ref(_window));
}

Game::~Game() {
    Py_Finalize();
}

void Game::run() {
    sf::Clock clock, updateFps;
    float lastTime = 0.f, currentTime, delta;

    if (_settings->getShowFpsCounter()) {
        auto theme = _resourceHandler->get<tgui::Theme>("default");
        tgui::Label::Ptr lblFps = theme->load("Label");
        lblFps->setTextColor(sf::Color::Yellow);
        lblFps->setTextSize(30);
        _gui.add(lblFps, "lblFps");
    }

    while (_window.isOpen()) {
        _stateHandler->handleTransition();

        sf::Event e;
        while (_window.pollEvent(e)) {
            if (e.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                _window.close();
            _stateHandler->handleEvent(e);
            _gui.handleEvent(e);
        }

        currentTime = clock.restart().asSeconds();
        delta = currentTime - lastTime;
        _stateHandler->update(delta);

        if (_settings->getShowFpsCounter()) {
            if (updateFps.getElapsedTime() > sf::seconds(1.f)) {
                auto lblFps = _gui.get<tgui::Label>("lblFps");
                lblFps->setText(std::to_string(unsigned(1.f / delta)));
                updateFps.restart();
            }
        }

        _window.clear();
        _stateHandler->draw(_window);
        _gui.draw();
        _window.display();
    }
}
