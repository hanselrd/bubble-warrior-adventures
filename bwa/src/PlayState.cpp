#include "PlayState.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <pugixml.hpp>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <functional>
#include <vector>
#include "ResourceLoader.hpp"
#include "StateHandler.hpp"

bwa::PlayState::PlayState(StateHandler& stateHandler, sf::RenderWindow& window, sol::state& lua)
	: GameState(stateHandler, lua) {
	_gui.setWindow(window);

	auto lblName = std::make_shared<tgui::Label>();
	lblName->setText("PlayState");
	lblName->setTextSize(40);
	lblName->setPosition(0, 300);
	_gui.add(lblName, "lblName");

	auto btnGoBack = std::make_shared<tgui::Button>();
	btnGoBack->setPosition(300, 0);
	btnGoBack->setText("Main Menu");
	btnGoBack->connect("pressed", [&] { _stateHandler.popState(); });
	_gui.add(btnGoBack, "btnGoBack");

	pugi::xml_document doc;
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
	}
}

void bwa::PlayState::handleEvents(sf::Event& e) {
	_gui.handleEvent(e);
}

void bwa::PlayState::update(float delta) {
}

void bwa::PlayState::draw(sf::RenderWindow& window) {
	_gui.draw();
}
