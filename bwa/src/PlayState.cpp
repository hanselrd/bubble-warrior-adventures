#include "PlayState.hpp"
#include <iostream>

bwa::PlayState::PlayState(sf::RenderWindow& window) {
	_gui.setWindow(window);
	auto lblName = std::make_shared<tgui::Label>();
	lblName->setText("PlayState");
	lblName->setTextSize(40);
	lblName->setPosition(0, 300);
	_gui.add(lblName, "lblName");
}

void bwa::PlayState::handleEvents(sf::Event& e) {
	_gui.handleEvent(e);
}

void bwa::PlayState::update(float delta) {
}

void bwa::PlayState::draw(sf::RenderWindow& window) {
	_gui.draw();
}
