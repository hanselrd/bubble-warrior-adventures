#pragma once
#include "GameState.hpp"

namespace bwa {
	class TitleScreen final : public GameState {
	public:
		explicit TitleScreen(StateHandler& stateHandler, sf::RenderWindow& window);
		TitleScreen(const TitleScreen&) = delete;
		TitleScreen& operator=(const TitleScreen&) = delete;

		void handleEvent(sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderWindow& window) override;
	};
}
