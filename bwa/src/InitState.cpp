#include "InitState.hpp"
#include <iostream>

bwa::InitState::InitState(sf::RenderWindow& window) {
	_gui.setWindow(window);
	auto lblName = std::make_shared<tgui::Label>();
	lblName->setText("InitState");
	lblName->setTextSize(40);
	lblName->setPosition(0, 300);
	_gui.add(lblName, "lblName");
}

void bwa::InitState::handleEvents(sf::Event& e) {
	_gui.handleEvent(e);
}

void bwa::InitState::update(float delta) {
}

void bwa::InitState::draw(sf::RenderWindow& window) {
	_gui.draw();
}
