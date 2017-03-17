#include "PlayScreen.hpp"
#include "Config.hpp"
#include "Locator.hpp"
#include "Script.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"

PlayScreen::PlayScreen(StateHandler& stateHandler, sf::RenderWindow& window)
    : State(stateHandler)
    , _map(MAPS_DIR "world.tmx") {
    _gui.setWindow(window);

    auto settings = Locator<Settings>::get();

    Script testConfig("test_config.py");
    testConfig("main");

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

void PlayScreen::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void PlayScreen::update(float delta) {
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

void PlayScreen::draw(sf::RenderWindow& window) {
    window.setView(_view);
    window.draw(_map.getLayers().at(0));
    window.draw(_map.getLayers().at(1));
    window.draw(_map.getLayers().at(2));
    window.draw(_player);
    window.draw(_map.getLayers().at(3));
    _gui.draw();
}
