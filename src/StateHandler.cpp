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
    _eventQueue.notify(Event::Pop, nullptr);
}

void StateHandler::handleTransition() {
    Event e;
    std::shared_ptr<State> state;

    while (_eventQueue.poll(e, state)) {
        switch (e) {
        case Event::Change:
            if (!_states.empty())
                _states.pop();
            _states.push(state);
            break;
        case Event::Push:
            if (!_states.empty())
                _states.top()->pause();
            _states.push(state);
            break;
        case Event::Pop:
            if (!_states.empty()) {
                _states.pop();
                if (!_states.empty())
                    _states.top()->resume();
            }
            break;
        }
    }
}

bool StateHandler::empty() const {
    return _states.empty();
}

std::size_t StateHandler::size() const {
    return _states.size();
}
