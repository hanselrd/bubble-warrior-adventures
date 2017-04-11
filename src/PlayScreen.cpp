#include "PlayScreen.hpp"
#include "Config.hpp"
#include "Locator.hpp"
#include "Player.hpp"
#include "ResourceHandler.hpp"
#include "Script.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"
#include "TitleScreen.hpp"

PlayScreen::PlayScreen(sf::RenderWindow& window)
    : _map("castle_interior_polygon_walls.tmx"),
      _player("regular_hero_male.png", 64) {
    _gui.setWindow(window);

    auto settings = Locator<Settings>::get();

    Script testConfig("test_config.py");
    testConfig("main");

    Script testTmx("test_tmx.py");
    testTmx("main", std::ref(_map));

    initializeOverlay(window);
    updateOverlay();
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
    //_player.setPosition(1446, 316);
    _player.setPosition(1446, 1400);

    _view.setCenter(_player.getPosition());
    _view.setSize((float)window.getSize().x, (float)window.getSize().y);
    _view.zoom(0.6f);
}

void PlayScreen::handleEvent(sf::Event& e) {
    _player.handleEvent(e);
    _gui.handleEvent(e);
}

void PlayScreen::update(float delta) {

    _delta = delta;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        _player.move(0, std::ceil(-70 * delta));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _player.move(std::ceil(-70 * delta), 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        _player.move(0, std::floor(70 * delta));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _player.move(std::floor(70 * delta), 0);

    auto playerPos = _player.getPosition();
    _player.update(delta);
    auto lblCoords = _gui.get<tgui::Label>("lblCoords");
    lblCoords->setText('(' + std::to_string(playerPos.x) + ',' + std::to_string(playerPos.y) + ')');

    for (const auto& layer : _map.getLayers()) {
        if (layer.getType() == Map::Layer::Type::Object) {
            for (const auto& object : layer.getObjects()) {
                sf::FloatRect intersection;
                while (Object::checkCollision(_player, object, intersection)) {
                    lblCoords->setText(lblCoords->getText() + " Collision!");
                    _player.move(intersection.width, 0);
                }
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

void PlayScreen::initializeOverlay(sf::RenderWindow &window)
{

    auto resourceHandler = Locator<ResourceHandler>::get();

    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    auto theme = resourceHandler->get<tgui::Theme>("default");

    auto lblCoords = tgui::Label::create();
    lblCoords->setTextColor(sf::Color::Cyan);
    lblCoords->setTextSize(30);
    lblCoords->setPosition(0, 30);
    _gui.add(lblCoords, "lblCoords");

    auto btnMainMenu = tgui::Button::create();
    btnMainMenu->setPosition(0, 60);
    btnMainMenu->setText("Main Menu");
    btnMainMenu->connect("pressed", [&] {
        Locator<StateHandler>::get()->push<TitleScreen>(std::ref(window));
    });
    _gui.add(btnMainMenu, "btnMainMenu");

    tgui::Panel::Ptr _panelPlayerStats = theme->load("Panel");
    _panelPlayerStats->setSize(windowWidth, 60);
    _panelPlayerStats->setPosition(0, windowHeight - _panelPlayerStats->getSize().y);

    // Offsets
    constexpr unsigned STATS_OFFSET = 170;

    auto lblName = tgui::Label::create("Player");
    lblName->setTextColor(sf::Color::White);
    lblName->setTextSize(25);
    lblName->setPosition(10, 0);
    _panelPlayerStats->add(lblName, "lblName");

    auto lblLevel = tgui::Label::create("Lv. " + std::to_string(_player.getLevel()));
    lblLevel->setTextColor(sf::Color::White);
    lblLevel->setTextSize(25);
    lblLevel->setPosition(10, _panelPlayerStats->getSize().y / 2);
    _panelPlayerStats->add(lblLevel, "lblLevel");

    auto lblHealth = tgui::Label::create("HP");
    lblHealth->setTextColor(sf::Color::White);
    lblHealth->setTextSize(15);
    lblHealth->setPosition(STATS_OFFSET, 0);
    _panelPlayerStats->add(lblHealth, "lblHealth");

    auto prgbarHealth = tgui::ProgressBar::create();
    prgbarHealth->getRenderer()->setBackgroundColor(sf::Color::Black);
    prgbarHealth->getRenderer()->setForegroundColor(sf::Color::Red);
    prgbarHealth->getRenderer()->setTextColor(sf::Color::White);
    prgbarHealth->setMaximum(_player.getMaxHealth());
    prgbarHealth->setMinimum(0);
    prgbarHealth->setSize(windowWidth / 5, prgbarHealth->getSize().y * 1.7);
    prgbarHealth->setPosition(lblHealth->getPosition().x, lblHealth->getTextSize());
    prgbarHealth->setValue(_player.getHealth());
    prgbarHealth->setText(std::to_string(prgbarHealth->getValue()) + "/" + std::to_string(prgbarHealth->getMaximum()));
    _panelPlayerStats->add(prgbarHealth, "prgbarHealth");

    auto lblMana = tgui::Label::create("MP");
    lblMana->setTextColor(sf::Color::White);
    lblMana->setTextSize(15);
    lblMana->setPosition(STATS_OFFSET + windowWidth / 4, 0);
    _panelPlayerStats->add(lblMana, "lblMana");

    auto prgbarMana = tgui::ProgressBar::create();
    prgbarMana->getRenderer()->setBackgroundColor(sf::Color::Black);
    prgbarMana->getRenderer()->setForegroundColor(sf::Color::Blue);
    prgbarMana->getRenderer()->setTextColor(sf::Color::White);
    prgbarMana->setMaximum(_player.getMaxMana());
    prgbarMana->setMinimum(0);
    prgbarMana->setSize(windowWidth / 5, prgbarMana->getSize().y * 1.7);
    prgbarMana->setPosition(lblMana->getPosition().x, lblMana->getTextSize());
    prgbarMana->setValue(_player.getMana());
    prgbarMana->setText(std::to_string(prgbarMana->getValue()) + "/" + std::to_string(prgbarMana->getMaximum()));
    _panelPlayerStats->add(prgbarMana, "prgbarMana");

    auto lblExperience = tgui::Label::create("EXP");
    lblExperience->setTextColor(sf::Color::White);
    lblExperience->setTextSize(15);
    lblExperience->setPosition(STATS_OFFSET + windowWidth / 2, 0);
    _panelPlayerStats->add(lblExperience, "lblExperience");

    auto prgbarExperience = tgui::ProgressBar::create();
    prgbarExperience->getRenderer()->setBackgroundColor(sf::Color::Black);
    prgbarExperience->getRenderer()->setForegroundColor(sf::Color::Green);
    prgbarExperience->getRenderer()->setTextColor(sf::Color::White);
    prgbarExperience->setMaximum(_player.getMaxExperience());
    prgbarExperience->setMinimum(0);
    prgbarExperience->setSize(windowWidth / 5, prgbarExperience->getSize().y * 1.7);
    prgbarExperience->setPosition(lblExperience->getPosition().x, lblExperience->getTextSize());
    prgbarExperience->setValue(_player.getExperience());
    prgbarExperience->setText(std::to_string(prgbarExperience->getValue()) + "/" + std::to_string(prgbarExperience->getMaximum()));
    _panelPlayerStats->add(prgbarExperience, "prgbarExperience");

    _gui.add(_panelPlayerStats, "_panelPlayerStats");

}

void PlayScreen::updateOverlay()
{
    //tgui::ProgressBar::Ptr hpbar = _playerPanelStats->get<tgui::ProgressBar>("prgbarHealth", true);
    //hpbar->setValue(3);
}
