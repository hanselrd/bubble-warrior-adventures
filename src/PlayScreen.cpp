#include "PlayScreen.hpp"
#include "Enemy.hpp"
#include "Config.hpp"
#include "Locator.hpp"
#include "ResourceHandler.hpp"
#include "Script.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"
#include "TitleScreen.hpp"
#include <iostream>

PlayScreen::PlayScreen(sf::RenderWindow& window)
    : _camera(window, _player)
    , _map("castle_interior_polygon_walls.tmx")
    , _player("regular_hero_male.png", "Jaime", 64) {
    _gui.setWindow(window);

    auto resourceHandler = Locator<ResourceHandler>::get();
    auto settings = Locator<Settings>::get();

    _mapHandler = std::make_shared<MapHandler>();
    Locator<MapHandler>::provide(_mapHandler);

    //Script testConfig("test_config.py");
    //testConfig("main");

    //Script testTmx("test_tmx.py");
    //testTmx("main", std::ref(_map));

    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    auto theme = resourceHandler->get<tgui::Theme>(THEME_DEFAULT);
    // NPC drawing/initialization
    // Edit this section with script code ******************************************************************
    _enemies.push_back(std::make_shared<Enemy>("golden_hero_male_no_shield.png", "enemy0", 64));
    _enemies.push_back(std::make_shared<Enemy>("golden_hero_female_no_shield_no_hat.png", "enemy1", 64));

    /************************************************************
    *GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*
    *************************************************************/
    {
    // Offsets
    constexpr unsigned STATS_OFFSET = 170;
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

        auto lblName = tgui::Label::create(_player.getName());
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
        prgbarExperience->setMaximum((unsigned int)_player.getMaxExp());
        prgbarExperience->setMinimum(0);
        prgbarExperience->setSize(windowWidth / 5, prgbarExperience->getSize().y * 1.7);
        prgbarExperience->setPosition(lblExperience->getPosition().x, lblExperience->getTextSize());
        prgbarExperience->setValue((unsigned int)_player.getExp());
        prgbarExperience->setText(std::to_string(prgbarExperience->getValue()) + "/" + std::to_string(prgbarExperience->getMaximum()));
        _panelPlayerStats->add(prgbarExperience, "prgbarExperience");

        _gui.add(_panelPlayerStats, "_panelPlayerStats");
    }
    /*******END*GUI*******/

    /* NOTE
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
    _enemies.at(0)->setPosition(1446, 1300);
    _enemies.at(1)->setPosition(1346, 1400);
    _player.setPosition(1446, 1320);
    _camera.setMap(&_map);
}

void PlayScreen::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void PlayScreen::update(float delta) {
    auto playerPosOld = _player.getPosition();
    _player.update(delta);
    for (int i = 0; i < _enemies.size(); i++) {
        _enemies[i]->update(delta);
    }
    _camera.update(delta);

    updateOverlay();
    auto playerPosNew = _player.getPosition();
    auto playerPos = _player.getPosition();

    auto lblCoords = _gui.get<tgui::Label>("lblCoords");
    lblCoords->setText('(' + std::to_string(playerPos.x) + ',' + std::to_string(playerPos.y) + ')');
    
    //*******************************************************
    //*COLLISION**COLLISION**COLLISION**COLLISION**COLLISION*
    //*******************************************************
    {
        for (const auto& layer : _map.getLayers()) {
            if (layer.getType() == Map::Layer::Type::Object) {
                for (const auto& object : layer.getObjects()) {
                    sf::FloatRect intersection;


                    if (Object::checkCollision(_player, object, intersection)) {
                        lblCoords->setText(lblCoords->getText() + " Collision!");

                        _player.move(playerPosOld - playerPosNew); // if collision, move player back, choppy but works
                    }
                }
            }
        }
    } //End Collision
}

void PlayScreen::draw(sf::RenderWindow& window) {
    window.draw(_map.getLayers().at(0));
    window.draw(_map.getLayers().at(1));
    window.draw(_map.getLayers().at(2));
    window.draw(_player);
    // Draws all the enemies in the vector
    for (int i = 0; i < _enemies.size(); i++) {
        window.draw(*_enemies.at(i));
    }
    window.draw(_map.getLayers().at(3));
    updateOverlay();
    _gui.draw();
}

void PlayScreen::updateOverlay()
{
    if (_overlayUpdate.getElapsedTime().asSeconds() >= 0.04f) {
        tgui::Label::Ptr lvl = _gui.get<tgui::Label>("lblLevel", true);
        lvl->setText("Lv. " + std::to_string(_player.getLevel()));

        tgui::ProgressBar::Ptr hpbar = _gui.get<tgui::ProgressBar>("prgbarHealth", true);
        hpbar->setValue(_player.getHealth());
        hpbar->setMaximum(_player.getMaxHealth());
        hpbar->setText(std::to_string(_player.getHealth()) + "/" + std::to_string(_player.getMaxHealth()));

        tgui::ProgressBar::Ptr mpbar = _gui.get<tgui::ProgressBar>("prgbarMana", true);
        mpbar->setValue(_player.getMana());
        mpbar->setMaximum(_player.getMaxMana());
        mpbar->setText(std::to_string(_player.getMana()) + "/" + std::to_string(_player.getMaxMana()));

        tgui::ProgressBar::Ptr expbar = _gui.get<tgui::ProgressBar>("prgbarExperience", true);
        expbar->setValue((unsigned)_player.getExp());
        expbar->setMaximum((unsigned)_player.getMaxExp());
        expbar->setText(std::to_string((int)_player.getExp()) + "/" + std::to_string((int)_player.getMaxExp()));

        _overlayUpdate.restart();
    }
}
