#pragma once
#include <sol.hpp>
#include "GameState.hpp"

namespace bwa {
	class InitState final : public GameState {
	public:
		InitState(StateHandler& stateHandler, sf::RenderWindow& window, const sol::state& lua);
		InitState(const InitState&) = delete;
		InitState& operator=(const InitState&) = delete;

		void handleEvents(sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderWindow& window) override;
	};
}
