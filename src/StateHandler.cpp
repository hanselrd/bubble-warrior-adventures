#include "StateHandler.hpp"

void StateHandler::handleEvent(sf::Event& e) {
	if (!_states.empty())
		_states.top()->handleEvent(e);
}

void StateHandler::update(float delta) {
	if (!_states.empty())
		_states.top()->update(delta);
}

void StateHandler::draw(sf::RenderWindow& window) {
	if (!_states.empty())
		_states.top()->draw(window);
}

void StateHandler::pop() {
	_event = Event::Pop;
}

void StateHandler::handleTransition() {
	switch (_event) {
	case Event::Change:
		if (!_states.empty())
			_states.pop();
		_states.push(std::move(_temp));
		break;
	case Event::Push:
		if (!_states.empty())
			_states.top()->pause();
		_states.push(std::move(_temp));
		break;
	case Event::Pop:
		if (!_states.empty()) {
			_states.pop();
			if (!_states.empty())
				_states.top()->resume();
		}
		break;
	}
	_event = Event::Null;
}
