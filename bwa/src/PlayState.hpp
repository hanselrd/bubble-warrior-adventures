#pragma once
#include <sol.hpp>
#include "GameState.hpp"

namespace bwa {
	class PlayState final : public GameState {
	public:
		PlayState(StateHandler& stateHandler, sf::RenderWindow& window, sol::state& lua);
		PlayState(const PlayState&) = delete;
		PlayState& operator=(const PlayState&) = delete;

		void handleEvents(sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderWindow& window) override;
	};
}
