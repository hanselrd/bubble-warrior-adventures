#include "StateHandler.hpp"

void bwa::StateHandler::handleEvents(sf::Event& e) {
	if (!_states.empty())
		_states.top()->handleEvents(e);
}

void bwa::StateHandler::update(float delta) {
	if (!_states.empty())
		_states.top()->update(delta);
}

void bwa::StateHandler::draw(sf::RenderWindow& window) {
	if (!_states.empty())
		_states.top()->draw(window);
}

void bwa::StateHandler::popState() {
	_event = Event::Pop;
}

void bwa::StateHandler::handleTransitions() {
	switch (_event) {
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
