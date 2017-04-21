#include "PlayScreen.hpp"
#include "Config.hpp"
#include "Locator.hpp"
#include "ResourceHandler.hpp"
#include "Script.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"
#include "TitleScreen.hpp"

PlayScreen::PlayScreen(sf::RenderWindow& window)
    : _camera(window, _player)
    , _map("world.tmx") {
    _gui.setWindow(window);

    auto resourceHandler = Locator<ResourceHandler>::get();
    auto settings = Locator<Settings>::get();

    _mapHandler = std::make_shared<MapHandler>();
    Locator<MapHandler>::provide(_mapHandler);

    Script testConfig("test_config.py");
    testConfig("main");

    Script testTmx("test_tmx.py");
    testTmx("main", std::ref(_map));

    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    auto theme = resourceHandler->get<tgui::Theme>(THEME_DEFAULT);

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
    _gui.add(btnMainMenu);

    tgui::Panel::Ptr panelPlayerStats = theme->load("Panel");
    panelPlayerStats->setSize(windowWidth, 60);
    panelPlayerStats->setPosition(0, windowHeight - panelPlayerStats->getSize().y);

    // Offsets
    constexpr unsigned STATS_OFFSET = 170;

    auto lblName = tgui::Label::create("1234567890");
    lblName->setTextColor(sf::Color::White);
    lblName->setTextSize(25);
    lblName->setPosition(10, 0);
    panelPlayerStats->add(lblName);

    auto lblLVL = tgui::Label::create("Lv. 67");
    lblLVL->setTextColor(sf::Color::White);
    lblLVL->setTextSize(25);
    lblLVL->setPosition(10, panelPlayerStats->getSize().y / 2);
    panelPlayerStats->add(lblLVL);

    auto lblHP = tgui::Label::create("HP");
    lblHP->setTextColor(sf::Color::White);
    lblHP->setTextSize(15);
    lblHP->setPosition(STATS_OFFSET, 0);
    panelPlayerStats->add(lblHP);

    auto prgbarHP = tgui::ProgressBar::create();
	prgbarHP->getRenderer()->setBackgroundColor(sf::Color::Black);
	prgbarHP->getRenderer()->setForegroundColor(sf::Color::Red);
	prgbarHP->getRenderer()->setTextColor(sf::Color::White);
	prgbarHP->setMaximum(10);
	prgbarHP->setMinimum(0);
    prgbarHP->setSize(windowWidth / 5, prgbarHP->getSize().y * 1.7);
    prgbarHP->setPosition(lblHP->getPosition().x, lblHP->getTextSize());
	prgbarHP->setValue(9);
	prgbarHP->setText(std::to_string(prgbarHP->getValue()) + "/" + std::to_string(prgbarHP->getMaximum()));
	panelPlayerStats->add(prgbarHP);

    auto lblMP = tgui::Label::create("MP");
    lblMP->setTextColor(sf::Color::White);
    lblMP->setTextSize(15);
    lblMP->setPosition(STATS_OFFSET + windowWidth / 4, 0);
    panelPlayerStats->add(lblMP);

    auto prgbarMP = tgui::ProgressBar::create();
	prgbarMP->getRenderer()->setBackgroundColor(sf::Color::Black);
	prgbarMP->getRenderer()->setForegroundColor(sf::Color::Blue);
	prgbarMP->getRenderer()->setTextColor(sf::Color::White);
	prgbarMP->setMaximum(10);
	prgbarMP->setMinimum(0);
    prgbarMP->setSize(windowWidth / 5, prgbarMP->getSize().y * 1.7);
	prgbarMP->setPosition(lblMP->getPosition().x, lblMP->getTextSize());
	prgbarMP->setValue(9);
	prgbarMP->setText(std::to_string(prgbarMP->getValue()) + "/" + std::to_string(prgbarMP->getMaximum()));
	panelPlayerStats->add(prgbarMP);

    auto lblEXP = tgui::Label::create("EXP");
    lblEXP->setTextColor(sf::Color::White);
    lblEXP->setTextSize(15);
    lblEXP->setPosition(STATS_OFFSET + windowWidth / 2, 0);
    panelPlayerStats->add(lblEXP);

    auto prgbarEXP = tgui::ProgressBar::create();
	prgbarEXP->getRenderer()->setBackgroundColor(sf::Color::Black);
	prgbarEXP->getRenderer()->setForegroundColor(sf::Color::Green);
	prgbarEXP->getRenderer()->setTextColor(sf::Color::Black);
	prgbarEXP->setMaximum(10);
	prgbarEXP->setMinimum(0);
    prgbarEXP->setSize(windowWidth / 5, prgbarEXP->getSize().y * 1.7);
	prgbarEXP->setPosition(lblEXP->getPosition().x, lblEXP->getTextSize());
	prgbarEXP->setValue(9);
	prgbarEXP->setText(std::to_string(prgbarEXP->getValue()) + "/" + std::to_string(prgbarEXP->getMaximum()));
	panelPlayerStats->add(prgbarEXP);

    _gui.add(panelPlayerStats);

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
    _player.setPosition(100, 100);
    _camera.setMap(&_map);
}

void PlayScreen::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void PlayScreen::update(float delta) {
    _player.update(delta);
    _camera.update(delta);

    auto playerPos = _player.getPosition();

    auto lblCoords = _gui.get<tgui::Label>("lblCoords");
    lblCoords->setText('(' + std::to_string(playerPos.x) + ',' + std::to_string(playerPos.y) + ')');

    for (const auto& layer : _map.getLayers()) {
        if (layer.getType() == Map::Layer::Type::Object) {
            for (const auto& object : layer.getObjects()) {
                sf::FloatRect intersection;
                if (Object::checkCollision(_player, object, intersection)) {
                    lblCoords->setText(lblCoords->getText() + " Collision!");
                    //_player.move(intersection.width, 0);
                }
            }
        }
    }
}

void PlayScreen::draw(sf::RenderWindow& window) {
    window.draw(_map.getLayers().at(0));
    window.draw(_map.getLayers().at(1));
    window.draw(_map.getLayers().at(2));
    window.draw(_player);
    window.draw(_map.getLayers().at(3));
    _gui.draw();
}
