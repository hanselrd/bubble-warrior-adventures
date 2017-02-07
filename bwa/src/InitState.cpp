#include "InitState.hpp"

bwa::InitState::InitState(sf::RenderWindow& window, const sol::state& lua) {
	_gui.setWindow(window);

	// Pulls the window dimensions from the window
	auto windowWidth = tgui::bindWidth(_gui);
	auto windowHeight = tgui::bindHeight(_gui);

	// To be used for the background of the window
	auto background = std::make_shared<tgui::Picture>();
	background->setTexture(lua["config"]["InitState"]["background"].get<std::string>());
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

	// Play button
	auto btnPlay = std::make_shared<tgui::Button>();
	btnPlay->setSize(windowWidth, 50);
	btnPlay->setPosition(0, windowHeight - 200);
	btnPlay->setText("Play");
	_gui.add(btnPlay);

	// Credits button
	auto btnCredits = std::make_shared<tgui::Button>();
	btnCredits->setSize(windowWidth, 50);
	btnCredits->setPosition(0, windowHeight - 150);
	btnCredits->setText("Credits");
	_gui.add(btnCredits);

	// Quit button
	auto btnQuit = std::make_shared<tgui::Button>();
	btnQuit->setSize(windowWidth, 50);
	btnQuit->setPosition(0, windowHeight - 100);
	btnQuit->setText("Quit");
	btnQuit->connect("pressed", [&] { window.close(); });
	_gui.add(btnQuit);
}

void bwa::InitState::handleEvents(sf::Event& e) {
	_gui.handleEvent(e);
}

void bwa::InitState::update(float delta) {
}

void bwa::InitState::draw(sf::RenderWindow& window) {
	_gui.draw();
}
