#include "PlayState.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <pugixml.hpp>
#include <sol.hpp>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <functional>
#include <vector>
#include "ResourceCache.hpp"
#include "StateHandler.hpp"

bwa::PlayState::PlayState(StateHandler& stateHandler, sf::RenderWindow& window)
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
	btnGoBack->connect("pressed", [&] { _stateHandler.popState(); });
	_gui.add(btnGoBack, "btnGoBack");

	_rect.setSize({ 20, 20 });
	_rect.setPosition(100, 100);
	_rect.setFillColor(sf::Color::Blue);

	_view.setCenter(_rect.getPosition());
	_view.setSize(window.getSize().x, window.getSize().y);

	/*pugi::xml_document doc;
	auto result = doc.load_file("assets/maps/world.tmx");
	if (result) {
		for (const auto& layer : doc.child("map").children("layer")) {
			std::string data = layer.child("data").child_value();
			data.erase(std::remove_if(std::begin(data), std::end(data), std::bind(std::isspace<char>, std::placeholders::_1, std::locale::classic())), std::end(data));
			std::vector<std::uint8_t> decoded = base64::decode(data);
			std::vector<std::uint32_t> gids(decoded.size() / 4);
			std::memcpy(gids.data(), decoded.data(), decoded.size());
			for (auto &gid : gids)
				std::cout << gid << " ";
			std::cout << std::endl;
		}
		auto map = doc.child("map");
		for (const auto& it : map) {
			std::cout << it.attribute("name").as_string() << std::endl;
		}
	}*/
}

void bwa::PlayState::handleEvent(sf::Event& e) {
	_gui.handleEvent(e);
}

void bwa::PlayState::update(float delta) {
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

void bwa::PlayState::draw(sf::RenderWindow& window) {
	window.setView(_view);
	window.draw(_rect);
	_gui.draw();
}
