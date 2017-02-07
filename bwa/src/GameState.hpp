#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

namespace bwa {
	class StateHandler;

	class GameState {
	public:
		GameState(StateHandler& stateHandler);
		GameState(const GameState&) = delete;
		GameState& operator=(const GameState&) = delete;

		virtual void handleEvents(sf::Event& e) = 0;
		virtual void update(float delta) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual void pause();
		virtual void resume();

	protected:
		tgui::Gui _gui;
		StateHandler& _stateHandler;
	};
}
