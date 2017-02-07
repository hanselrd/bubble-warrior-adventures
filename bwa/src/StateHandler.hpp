#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <stack>
#include "GameState.hpp"

namespace bwa {
	class StateHandler {
	public:
		StateHandler() = default;
		StateHandler(const StateHandler&) = delete;
		StateHandler& operator=(const StateHandler&) = delete;

		void handleEvents(sf::Event& e);
		void update(float delta);
		void draw(sf::RenderWindow& window);

		template <typename State, typename... Args>
		void pushState(Args&&... args) {
			auto state = std::make_unique<State>(std::forward<Args>(args)...);
			if (!_states.empty())
				_states.top()->pause();
			_states.push(std::move(state));
		}

		void popState() {
			if (!_states.empty()) {
				_states.pop();
				if (!_states.empty())
					_states.top()->resume();
			}
		}

	private:
		std::stack<std::unique_ptr<GameState>> _states;
	};
}
