#include "PlayScreen.hpp"
#include "Config.hpp"
#include "Locator.hpp"
#include "ResourceHandler.hpp"
#include "Script.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"
#include "TitleScreen.hpp"

PlayScreen::PlayScreen(sf::RenderWindow& window)
    : _map("world.tmx")
    , _player(8, sf::Color(0xFF9900FF)) {
    _gui.setWindow(window);

    auto resourceHandler = Locator<ResourceHandler>::get();
    auto settings = Locator<Settings>::get();

    Script testConfig("test_config.py");
    testConfig("main");

    Script testTmx("test_tmx.py");
    testTmx("main", std::ref(_map));

    auto lblCoords = std::make_shared<tgui::Label>();
    lblCoords->setTextColor(sf::Color::Cyan);
    lblCoords->setTextSize(30);
    lblCoords->setPosition(0, 30);
    _gui.add(lblCoords, "lblCoords");

    auto btnMainMenu = std::make_shared<tgui::Button>();
    btnMainMenu->setPosition(0, 60);
    btnMainMenu->setText("Main Menu");
    btnMainMenu->connect("pressed", [&] {
        Locator<StateHandler>::get()->push<TitleScreen>(std::ref(window));
    });
    _gui.add(btnMainMenu);

    /*
        Don't put the map in the resource cache because
        it contains a sf::Texture for each tileset
        which stays alive longer than the sf::RenderWindow
        and results in the game crashing
    */

    //_player.setRadius(8);
    //_player.setFillColor(sf::Color::Cyan);
    //auto playerSpawn = _map.getLayers()[2].getObjs()[0].getRect();
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

    for (const auto& layer : _map.getLayers()) {
        if (layer.getType() == Map::Layer::Type::Object) {
            for (const auto& object : layer.getObjects()) {
                if (Object::checkCollision(_player, object))
                    lblCoords->setText(lblCoords->getText() + " Collision!");
            }
        }
    }

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
