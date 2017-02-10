#include "GameState.hpp"

bwa::GameState::GameState(bwa::StateHandler& stateHandler, sol::state& lua)
	: _stateHandler(stateHandler)
	, _lua(lua) {}

void bwa::GameState::pause() {
	// default pause behavior
}

void bwa::GameState::resume() {
	// default resume behavior
}
