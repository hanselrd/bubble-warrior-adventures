#include "InitState.hpp"
#include <sol.hpp>
#include "PlayState.hpp"
#include "ResourceCache.hpp"
#include "StateHandler.hpp"

bwa::InitState::InitState(StateHandler& stateHandler, sf::RenderWindow& window)
	: GameState(stateHandler) {
	_gui.setWindow(window);
	
	// Gets the lua state from ResourceCache
	auto luaConfig = ResourceCache<sol::state>::get("config");

	// Pulls the window dimensions from the window
	auto windowWidth = tgui::bindWidth(_gui);
	auto windowHeight = tgui::bindHeight(_gui);

	// To be used for the background of the window
	auto background = std::make_shared<tgui::Picture>();
	background->setTexture((*luaConfig)["config"]["InitState"]["background"].get<std::string>());
	_gui.add(background);

	// "Bubble Warrior" text component
	auto lblTitle1 = std::make_shared<tgui::Label>();
	lblTitle1->setTextSize(72);
	lblTitle1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	lblTitle1->setSize(windowWidth, 500);
	lblTitle1->setPosition(0, windowHeight / 5);
	lblTitle1->setText("Bubble Warrior");
	lblTitle1->setTextColor(sf::Color::Black);
	_gui.add(lblTitle1);

	// "Adventures" text component
	auto lblTitle2 = std::make_shared<tgui::Label>();
	lblTitle2->setTextSize(72);
	lblTitle2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	lblTitle2->setSize(windowWidth, 500);
	lblTitle2->setPosition(0, windowHeight * 7 / 20);
	lblTitle2->setText("Adventures!");
	lblTitle2->setTextColor(sf::Color::Black);
	_gui.add(lblTitle2);

	// Constants for button location
	constexpr unsigned BUTTON_HEIGHT = 50;
	constexpr unsigned BUTTON_Y_OFFSET = 240;

	// Play button
	auto btnPlay = std::make_shared<tgui::Button>();
	btnPlay->setSize(windowWidth, BUTTON_HEIGHT);
	btnPlay->setPosition(0, windowHeight - BUTTON_Y_OFFSET);
	btnPlay->setText("Play");
	btnPlay->connect("pressed", [&] { _stateHandler.pushState<PlayState>(std::ref(window)); });
	_gui.add(btnPlay);

	// Settings button
	auto btnSettings = std::make_shared<tgui::Button>();
	btnSettings->setSize(windowWidth, BUTTON_HEIGHT);
	btnSettings->setPosition(0, windowHeight - BUTTON_Y_OFFSET + BUTTON_HEIGHT);
	btnSettings->setText("Settings");
	_gui.add(btnSettings);

	// Credits button
	auto btnCredits = std::make_shared<tgui::Button>();
	btnCredits->setSize(windowWidth, BUTTON_HEIGHT);
	btnCredits->setPosition(0, windowHeight - BUTTON_Y_OFFSET + (BUTTON_HEIGHT * 2));
	btnCredits->setText("Credits");
	_gui.add(btnCredits);

	// Exit button
	auto btnExit = std::make_shared<tgui::Button>();
	btnExit->setSize(windowWidth, BUTTON_HEIGHT);
	btnExit->setPosition(0, windowHeight - BUTTON_Y_OFFSET + (BUTTON_HEIGHT * 3));
	btnExit->setText("Exit");
	btnExit->connect("pressed", [&] { window.close(); });
	_gui.add(btnExit);
}

void bwa::InitState::handleEvent(sf::Event& e) {
	_gui.handleEvent(e);
}

void bwa::InitState::update(float delta) {
}

void bwa::InitState::draw(sf::RenderWindow& window) {
	_gui.draw();
}
