#include "PlayState.hpp"
#include <sol.hpp>
#include "ResourceCache.hpp"
#include "StateHandler.hpp"
#include "Tmx.hpp"

PlayState::PlayState(StateHandler& stateHandler, sf::RenderWindow& window)
	: GameState(stateHandler) {
	_gui.setWindow(window);

	// Gets the lua state from ResourceCache
	auto luaConfig = ResourceCache<sol::state>::get("config");

	auto lblCoords = std::make_shared<tgui::Label>();
	lblCoords->setTextColor(sf::Color::Blue);
	lblCoords->setTextSize(30);
	lblCoords->setPosition(0, 30);
	_gui.add(lblCoords, "lblCoords");

	auto btnGoBack = std::make_shared<tgui::Button>();
	btnGoBack->setPosition(0, 60);
	btnGoBack->setText("Main Menu");
	btnGoBack->connect("pressed", [&] { _stateHandler.pop(); });
	_gui.add(btnGoBack);

	_rect.setSize({ 16, 16 });
	_rect.setPosition(100, 100);
	_rect.setFillColor(sf::Color::Blue);

	_view.setCenter(_rect.getPosition());
	_view.setSize(window.getSize().x, window.getSize().y);
	_view.zoom(0.5);

	// change to use luaConfig eventually
	auto tmxWorld = ResourceCache<tmx::Map>::create("world", "assets/maps/world.tmx");
	std::cout << tmxWorld->getWidth() << std::endl;
	std::cout << tmxWorld->getHeight() << std::endl;
	std::cout << tmxWorld->getTileWidth() << std::endl;
	std::cout << tmxWorld->getTileHeight() << std::endl;
}

void PlayState::handleEvent(sf::Event& e) {
	_gui.handleEvent(e);
}

void PlayState::update(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_rect.move(0, -70 * delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_rect.move(-70 * delta, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_rect.move(0, 70 * delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_rect.move(70 * delta, 0);

	auto rectPos = _rect.getPosition();
	auto lblCoords = _gui.get<tgui::Label>("lblCoords");
	lblCoords->setText('(' + std::to_string(rectPos.x) + ',' + std::to_string(rectPos.y) + ')');

	_view.setCenter(_rect.getPosition());
}

void PlayState::draw(sf::RenderWindow& window) {
	window.setView(_view);
	window.draw(_rect);
	_gui.draw();
}
