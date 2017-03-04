#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <stack>
#include "GameState.hpp"

class StateHandler {
public:
    void handleEvent(sf::Event& e);
    void update(float delta);
    void draw(sf::RenderWindow& window);

    template <class State, class... Args>
    inline void change(Args&&... args) {
        helper<State>(Event::Change, std::forward<Args>(args)...);
    }

    template <class State, class... Args>
    inline void push(Args&&... args) {
        helper<State>(Event::Push, std::forward<Args>(args)...);
    }

    void pop();
    void handleTransition();

private:
    enum class Event {
        Null,
        Change,
        Push,
        Pop
    } _event;
    std::unique_ptr<GameState> _temp;
    std::stack<std::unique_ptr<GameState>> _states;

    template <typename State, typename... Args>
    inline void helper(const Event e, Args&&... args) {
        _temp = std::make_unique<State>(std::ref(*this), std::forward<Args>(args)...);
        _event = e;
    }
};