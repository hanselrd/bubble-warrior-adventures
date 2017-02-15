#include "GameState.hpp"

GameState::GameState(StateHandler& stateHandler)
	: _stateHandler(stateHandler) {}

void GameState::pause() {
	// default pause behavior
}

void GameState::resume() {
	// default resume behavior
}
