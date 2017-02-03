#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGui.hpp>
#include "GameState.hpp"

namespace bwa {
	class MainMenu : public GameState {
	public:
		MainMenu(sf::RenderWindow& window);
		void draw(sf::RenderWindow &window);
		void handleEvents(sf::Event &e);
		void update(float delta);

	private:
		void loadDrawables(tgui::Gui& gui); // should be priv
		void buttonClicked(std::string s);
		tgui::Gui _gui;
	};
}