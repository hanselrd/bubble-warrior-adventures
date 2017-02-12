#include "GameState.hpp"

bwa::GameState::GameState(StateHandler& stateHandler)
	: _stateHandler(stateHandler) {}

void bwa::GameState::pause() {
	// default pause behavior
}

void bwa::GameState::resume() {
	// default resume behavior
}
