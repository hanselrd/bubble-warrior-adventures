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
