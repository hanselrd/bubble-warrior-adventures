#include "PlayScreen.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
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

    auto playerSpawn = _map.getLayers()[5].getObjects()[0].getRect();
    _player.setPosition(playerSpawn.left, playerSpawn.top);

    // NPC drawing/initialization
    // Edit this section with script code ******************************************************************
 /*   _entities.push_back(std::make_shared<Enemy>("golden_hero_male_no_shield.png", "enemy0", 64));
    _entities.push_back(std::make_shared<Enemy>("golden_hero_female_no_shield_no_hat.png", "enemy1", 64));
*/
    /************************************************************
    *GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*GUI*
    *************************************************************/
    {
    // Offsets
    constexpr unsigned STATS_OFFSET = 170;
        lblCoords = tgui::Label::create();
        lblCoords->setTextColor(sf::Color::Cyan);
        lblCoords->setTextSize(30);
        lblCoords->setPosition(0, 30);
        _gui.add(lblCoords, "lblCoords");

        btnMainMenu = tgui::Button::create();
        btnMainMenu->setPosition(0, 60);
        btnMainMenu->setText("Main Menu");
        btnMainMenu->connect("pressed", [&] {
            Locator<StateHandler>::get()->push<TitleScreen>(std::ref(window));
        });
        _gui.add(btnMainMenu, "btnMainMenu");

        _panelPlayerStats = theme->load("Panel");
        _panelPlayerStats->setSize(windowWidth, 60);
        _panelPlayerStats->setPosition(0, windowHeight - _panelPlayerStats->getSize().y);

        lblName = tgui::Label::create(_player.getName());
        lblName->setTextColor(sf::Color::White);
        lblName->setTextSize(25);
        lblName->setPosition(10, 0);
        _panelPlayerStats->add(lblName, "lblName");

        lblLevel = tgui::Label::create("Lv. " + std::to_string(_player.getLevel()));
        lblLevel->setTextColor(sf::Color::White);
        lblLevel->setTextSize(25);
        lblLevel->setPosition(10, _panelPlayerStats->getSize().y / 2);
        _panelPlayerStats->add(lblLevel, "lblLevel");

        lblHealth = tgui::Label::create("HP");
        lblHealth->setTextColor(sf::Color::White);
        lblHealth->setTextSize(15);
        lblHealth->setPosition(STATS_OFFSET, 0);
        _panelPlayerStats->add(lblHealth, "lblHealth");

        prgbarHealth = tgui::ProgressBar::create();
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

        lblMana = tgui::Label::create("MP");
        lblMana->setTextColor(sf::Color::White);
        lblMana->setTextSize(15);
        lblMana->setPosition(STATS_OFFSET + windowWidth / 4, 0);
        _panelPlayerStats->add(lblMana, "lblMana");

        prgbarMana = tgui::ProgressBar::create();
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

        lblExperience = tgui::Label::create("EXP");
        lblExperience->setTextColor(sf::Color::White);
        lblExperience->setTextSize(15);
        lblExperience->setPosition(STATS_OFFSET + windowWidth / 2, 0);
        _panelPlayerStats->add(lblExperience, "lblExperience");

        prgbarExperience = tgui::ProgressBar::create();
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

    // The initial load entities to initialize the entity vectors
    updateEntitiesForCurrentMap();
    
    // Initializes the map to the _map variable
    // To change maps for portals, use '_map = mapInput;'
    _camera.setMap(&_map);
}

void PlayScreen::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void PlayScreen::updateEntitiesForCurrentMap() {
    //*******************************************************
    //*COLLISION**COLLISION**COLLISION**COLLISION**COLLISION*
    // All code below is 
    //*******************************************************
    {
        auto playerPosOld = _player.getPosition();
        // How to handle object collision
        for (const auto& layer : _map.getLayers()) {
            if (layer.getType() == Map::Layer::Type::Object) {
                for (const auto& object : layer.getObjects()) {
                    sf::FloatRect intersection;
                    // Cleck if collision occurs
                    if (Object::checkCollision(_player, object, intersection)) {
                        lblCoords->setText(lblCoords->getText() + " Collision!");
                        _player.setPosition(playerPosOld); // if collision, move player back, choppy but works
                    }
                }
            }
            //How to handle enemy collision
            else if (layer.getType() == Map::Layer::Type::Enemy) {
                for (const auto& object : layer.getObjects()) {
                    sf::FloatRect intersection;
                    // Cleck if collision occurs
                    if (Object::checkCollision(_player, object, intersection)) {
                        lblCoords->setText(lblCoords->getText() + " Collision!");
                        _player.setPosition(playerPosOld); // if collision, move player back, choppy but works
                    }
                }
            }
            // How to handle NPC collision
            else if (layer.getType() == Map::Layer::Type::NPC) {
                for (const auto& object : layer.getObjects()) {
                    sf::FloatRect intersection;
                    // Cleck if collision occurs
                    if (Object::checkCollision(_player, object, intersection)) {
                        lblCoords->setText(lblCoords->getText() + " Collision!");
                        _player.setPosition(playerPosOld); // if collision, move player back, choppy but works
                    }
                }
            }
            // How to handle Item collision
            else if (layer.getType() == Map::Layer::Type::Item) {
                for (const auto& object : layer.getObjects()) {
                    sf::FloatRect intersection;
                    // Cleck if collision occurs
                    if (Object::checkCollision(_player, object, intersection)) {
                        lblCoords->setText(lblCoords->getText() + " Collision!");
                        _player.setPosition(playerPosOld); // if collision, move player back, choppy but works
                    }
                }
            }
            // How to handle Portal collision
            else if (layer.getType() == Map::Layer::Type::Portal) {
                for (const auto& object : layer.getObjects()) {
                    sf::FloatRect intersection;
                    // Cleck if collision occurs
                    if (Object::checkCollision(_player, object, intersection)) {
                        lblCoords->setText(lblCoords->getText() + " Collision!");
                        _player.setPosition(playerPosOld); // if collision, move player back, choppy but works
                    }
                }
            }
            // How to handle Spawn collision
            else if (layer.getType() == Map::Layer::Type::Spawn) {
                for (const auto& object : layer.getObjects()) {
                    sf::FloatRect intersection;
                    // Cleck if collision occurs
                    if (Object::checkCollision(_player, object, intersection)) {
                        //lblCoords->setText(lblCoords->getText() + " Collision!");
                        //_player.setPosition(playerPosOld); // if collision, move player back, choppy but works
                    }
                }
            }
        }
    }//End Collision
    //for(auto layer : )
}
void PlayScreen::update(float delta) {

    updateEntitiesForCurrentMap();
    // Calling all entity/camera update functions
    _player.update(delta);
    for (int i = 0; i < _enemies.size(); i++) {
        _enemies[i]->update(delta);
    }
    for (int i = 0; i < _items.size(); i++) {
        _items[i]->update(delta);
    }
    for (int i = 0; i < _npcs.size(); i++) {
        _npcs[i]->update(delta);
    }
    _camera.update(delta);
    // End update functions

    updateOverlay();
    auto playerPosNew = _player.getPosition();
    auto playerPos = _player.getPosition();

    auto lblCoords = _gui.get<tgui::Label>("lblCoords");
    lblCoords->setText('(' + std::to_string(playerPos.x) + ',' + std::to_string(playerPos.y) + ')');
 
}

void PlayScreen::draw(sf::RenderWindow& window) {

    // Draw all layers in tmx file
    for (int i = 0; i < _map.getLayers().size(); i++) {
        window.draw(_map.getLayers().at(i));
    }
    //********************* Draw Player*******************
    window.draw(_player);

    // Draws all the enemies in the vector
    for (int i = 0; i < _enemies.size(); i++) {
        window.draw(*_enemies.at(i));
    }
    for (int i = 0; i < _items.size(); i++) {
        window.draw(*_items.at(i));
    }
    for (int i = 0; i < _objects.size(); i++) {
        window.draw(*_objects.at(i));
    }
    for (int i = 0; i < _npcs.size(); i++) {
        window.draw(*_npcs.at(i));
    }
    window.draw(_map.getLayers().at(2));
    updateOverlay();
    _gui.draw();
}

void PlayScreen::reloadObjects(Entity::EntityType type)
{ 
    _enemies.clear();
    _npcs.clear();
    //Grabbing all layers to process out the entity types
    for (const auto& layer : _map.getLayers()) {

        // Check the Map::Object::Type variable 
        auto layer_type = layer.getType();        
        Entity::EntityType conversion;
        //if (layer.getType() == Map::Layer::Type::Object) {
        //    for (const auto& object : layer.getObjects()) {
        //        _objects.push_back(std::make_shared<Object>(Object(object)));
        //    }
        //}
        //if (layer.getType() == Map::Layer::Type::Object) {
        //    for (const auto& object : layer.getObjects()) {
        //        _objects.push_back(std::make_shared<Object>(Object(object)));
        //    }
        //}
        if (layer.getType() == Map::Layer::Type::Enemy) {
            for (const auto& object : layer.getObjects()) {
                _enemies.push_back(std::make_shared<Enemy>(Enemy(object)));
            }
        }        
        if (layer.getType() == Map::Layer::Type::NPC) {
            for (const auto& object : layer.getObjects()) {
                _npcs.push_back(std::make_shared<NPC>(NPC(object)));
            }
        }
    }
}

void PlayScreen::updateOverlay()
{
    if (_overlayUpdate.getElapsedTime().asSeconds() >= 0.04f) {
        tgui::Label::Ptr lvl = _gui.get<tgui::Label>("lblLevel", true);
        lvl->setText("Lv. " + std::to_string(_player.getLevel()));

        tgui::ProgressBar::Ptr hpbar = _gui.get<tgui::ProgressBar>("prgbarHealth", true);
        hpbar->setMaximum(_player.getMaxHealth());
        hpbar->setValue(_player.getHealth());
        hpbar->setText(std::to_string(_player.getHealth()) + "/" + std::to_string(_player.getMaxHealth()));

        tgui::ProgressBar::Ptr mpbar = _gui.get<tgui::ProgressBar>("prgbarMana", true);
        mpbar->setMaximum(_player.getMaxMana());
        mpbar->setValue(_player.getMana());
        mpbar->setText(std::to_string(_player.getMana()) + "/" + std::to_string(_player.getMaxMana()));

        tgui::ProgressBar::Ptr expbar = _gui.get<tgui::ProgressBar>("prgbarExperience", true);
        expbar->setMaximum((unsigned)_player.getMaxExp());
        expbar->setValue((unsigned)_player.getExp());
        expbar->setText(std::to_string((int)_player.getExp()) + "/" + std::to_string((int)_player.getMaxExp()));

        _overlayUpdate.restart();
    }
}

std::vector<std::shared_ptr<NPC>>& PlayScreen::getNPCs()
{
    return _npcs;
}

std::vector<std::shared_ptr<Item>>& PlayScreen::getItems() {
    return _items;
}

std::vector<std::shared_ptr<Object>>& PlayScreen::getObjects() {
    return _objects;
}

std::vector<std::shared_ptr<Enemy>>& PlayScreen::getEnemies() {
    return _enemies;
}