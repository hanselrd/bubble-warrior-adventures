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
		void pushState(Args&&... args);

		void popState();
		void handleTransitions();

	private:
		enum class Event {
			Null,
			Push,
			Pop
		} _event;
		std::unique_ptr<GameState> _temp;
		std::stack<std::unique_ptr<GameState>> _states;
	};

	template<typename State, typename ...Args>
	inline void StateHandler::pushState(Args&& ...args) {
		_temp = std::make_unique<State>(std::ref(*this), std::forward<Args>(args)...);
		_event = Event::Push;
	}
}
