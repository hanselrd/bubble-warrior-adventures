#pragma once
#include "GameState.hpp"

namespace bwa {
	class InitState final : public GameState {
	public:
		explicit InitState(StateHandler& stateHandler, sf::RenderWindow& window);
		InitState(const InitState&) = delete;
		InitState& operator=(const InitState&) = delete;

		void handleEvent(sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderWindow& window) override;
	};
}
