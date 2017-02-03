#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGui.hpp>
#include "GameState.hpp"

namespace bwa {
	class MainMenu : public GameState {
	public:
		MainMenu();
		void draw(sf::RenderWindow &window);
		void handleEvents(sf::Event &e);
		void update(float delta);
		void bwa::MainMenu::loadDrawables(tgui::Gui & gui);
	private:
		void buttonClicked(std::string s);
		tgui::Gui _gui;
	};
}