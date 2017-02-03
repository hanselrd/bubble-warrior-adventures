#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/Gui.hpp>
#include "GameState.hpp"

namespace bwa {
	class TitleScreen : public GameState {
	public:
		TitleScreen();
		void draw(sf::RenderWindow &window);
		void handleEvents(sf::Event &e);
		void update(float delta);
		void bwa::TitleScreen::loadDrawables(tgui::Gui & gui);
	private:
		void buttonClicked(std::string s);
		tgui::Gui _gui;
	};
}