#include "PlayState.hpp"
#include <pybind11/eval.h>
namespace py = pybind11;
#include "Config.hpp"
#include "Locator.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"

PlayState::PlayState(StateHandler& stateHandler, sf::RenderWindow& window)
    : GameState(stateHandler)
    , _map(MAPS_DIR "world.tmx") {
    _gui.setWindow(window);

    // Locates and gets the Settings object
    auto settings = Locator<Settings>::get();

    // Call test scripts @@@@@@@@@@@@
    // These tests will be removed when the map loader in finished

    auto global = py::dict(py::module::import("__main__").attr("__dict__"));
    auto local = py::dict();
    py::eval_file(SCRIPTS_DIR "test_config.py", global, local);
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

    /*
        Don't put the map in the resource cache because
        it contains a sf::Texture for each tileset
        which stays alive longer than the sf::RenderWindow
        and results in the game crashing
    */

    _player.setRadius(8);
    _player.setFillColor(sf::Color::Cyan);
    //auto playerSpawn = _map.getLayers()[2].getObjects()[0].getRect();
    //_player.setPosition(playerSpawn.left, playerSpawn.top);
    _player.setPosition(100, 100);

    _view.setCenter(_player.getPosition());
    _view.setSize(window.getSize().x, window.getSize().y);
    _view.zoom(0.5);
}

void PlayState::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void PlayState::update(float delta) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        _player.move(0, std::ceil(-70 * delta));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _player.move(std::ceil(-70 * delta), 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        _player.move(0, std::floor(70 * delta));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _player.move(std::floor(70 * delta), 0);

    auto playerPos = _player.getPosition();

    auto lblCoords = _gui.get<tgui::Label>("lblCoords");
    lblCoords->setText('(' + std::to_string(playerPos.x) + ',' + std::to_string(playerPos.y) + ')');

    _view.setCenter(playerPos);
}

void PlayState::draw(sf::RenderWindow& window) {
    window.setView(_view);
    window.draw(_map.getLayers().at(0));
    window.draw(_map.getLayers().at(1));
    window.draw(_map.getLayers().at(2));
    window.draw(_player);
    window.draw(_map.getLayers().at(3));
    _gui.draw();
}
