#include "PlayState.hpp"
#include <pybind11/eval.h>
namespace py = pybind11;
#include "ResourceCache.hpp"
#include "StateHandler.hpp"
#include "Tmx.hpp"

PlayState::PlayState(StateHandler& stateHandler, sf::RenderWindow& window)
	: GameState(stateHandler) {
	_gui.setWindow(window);

	// Gets the global python scope from ResourceCache
	auto pyGlobal = ResourceCache<py::dict>::get("global");

	auto lblCoords = std::make_shared<tgui::Label>();
	lblCoords->setTextColor(sf::Color::Cyan);
	lblCoords->setTextSize(30);
	lblCoords->setPosition(0, 30);
	_gui.add(lblCoords, "lblCoords");

	auto btnGoBack = std::make_shared<tgui::Button>();
	btnGoBack->setPosition(0, 60);
	btnGoBack->setText("Main Menu");
	btnGoBack->connect("pressed", [&] { _stateHandler.pop(); });
	_gui.add(btnGoBack);

	_box.setSize({ 200, 60 });
	_box.setFillColor(sf::Color::Red);
	_box.setPosition(50, 50);

	_player.setRadius(8);
	_player.setFillColor(sf::Color::Cyan);
	_player.setPosition(300, 100);

	_view.setCenter(_player.getPosition());
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
		_player.move(0, -70 * delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_player.move(-70 * delta, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_player.move(0, 70 * delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_player.move(70 * delta, 0);

	auto playerPos = _player.getPosition();
	auto lblCoords = _gui.get<tgui::Label>("lblCoords");
	lblCoords->setText('(' + std::to_string(playerPos.x) + ',' + std::to_string(playerPos.y) + ')');

	_view.setCenter(_player.getPosition());
}

void PlayState::draw(sf::RenderWindow& window) {
	window.setView(_view);
	window.draw(_box);
	window.draw(_player);
	_gui.draw();
}
