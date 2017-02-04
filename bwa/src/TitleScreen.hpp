#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "GameState.hpp"

namespace bwa {
	class TitleScreen : public GameState {
	public:
		TitleScreen(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
		void handleEvents(sf::Event &e);
		void update(float delta);
	private:
		tgui::Gui _gui;
		void loadDrawables(tgui::Gui &gui);
	};
}