#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "State.hpp"

class StateHandler {
public:
    void handleEvent(sf::Event& e);
    void update(float delta);
    void draw(sf::RenderWindow& window);
    template <class State, class... Args>
        void change(Args&&... args);
    template <class State, class... Args>
        void push(Args&&... args);
    void pop();
    void handleTransition();

private:
    enum class Event {
        Null,
        Change,
        Push,
        Pop
    };

    template <typename State, typename... Args>
    void helper(const Event e, Args&&... args);

    Event _event;
    std::unique_ptr<State> _temp;
    std::stack<std::unique_ptr<State>> _states;
};

#include "StateHandler.tpp"
