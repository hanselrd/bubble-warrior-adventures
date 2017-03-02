#include "PlayState.hpp"
#include <pybind11/eval.h>
namespace py = pybind11;
#include "ResourceCache.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"

PlayState::PlayState(StateHandler& stateHandler, sf::RenderWindow& window)
    : GameState(stateHandler)
    , _map("assets/maps/world.tmx") {
    _gui.setWindow(window);

    // Gets the settings from the ResourceCache
    auto settings = ResourceCache<Settings>::get("settings");

    // Call test scripts @@@@@@@@@@@@
    // These tests will be removed when the map loader in finished
    std::string scripts = "assets/scripts/";

    auto global = py::dict(py::module::import("__main__").attr("__dict__"));
    auto local = py::dict();
    py::eval_file(scripts + "test_config.py", global, local);
    local["main"].cast<py::function>()();

    // write a script handler
    /*py::print();

    auto local2 = py::dict();
    py::eval_file(scripts + "test_tmx.py", *pyGlobal, local2);
    local2["main"].cast<py::function>().call();*/

    auto lblCoords = std::make_shared<tgui::Label>();
    lblCoords->setTextColor(sf::Color::Cyan);
    lblCoords->setTextSize(30);
    lblCoords->setPosition(0, 30);
    _gui.add(lblCoords, "lblCoords");

    auto btnGoBack = std::make_shared<tgui::Button>();
    btnGoBack->setPosition(0, 60);
    btnGoBack->setText("Main Menu");
    btnGoBack->connect("pressed", [&] { _stateHandler.pop(); });
    _gui.add(btnGoBack);

    _box.setSize({ 200, 60 });
    _box.setFillColor(sf::Color::Red);
    _box.setPosition(300, 50);

    /*
        Don't put the map in the resource cache because
        it contains a sf::Texture for each tileset
        which stays alive longer than the sf::RenderWindow
        and results in the game crashing
    */

    _player.setRadius(8);
    _player.setFillColor(sf::Color::Cyan);
    auto playerSpawn = _map.getLayers()[2].getObjects()[0].getRect();
    _player.setPosition(playerSpawn.left, playerSpawn.top);

    _view.setCenter(_player.getPosition());
    _view.setSize(window.getSize().x, window.getSize().y);
    _view.zoom(0.5);
}

void PlayState::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void PlayState::update(float delta) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        _player.move(0, -70 * delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _player.move(-70 * delta, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        _player.move(0, 70 * delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _player.move(70 * delta, 0);

    auto playerPos = _player.getPosition();
    auto lblCoords = _gui.get<tgui::Label>("lblCoords");
    lblCoords->setText('(' + std::to_string(playerPos.x) + ',' + std::to_string(playerPos.y) + ')');

    _view.setCenter(_player.getPosition());
}

void PlayState::draw(sf::RenderWindow& window) {
    window.setView(_view);
    window.draw(_map.getLayers().at(0));
    window.draw(_map.getLayers().at(1));
    window.draw(_map.getLayers().at(2));
    window.draw(_player);
    window.draw(_map.getLayers().at(3));
    // window.draw(_box);
    _gui.draw();
}
