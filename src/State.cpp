#include "State.hpp"

State::State(StateHandler& stateHandler)
    : _stateHandler(stateHandler) {}

void State::pause() {
    // default pause behavior
}

void State::resume() {
    // default resume behavior
}
