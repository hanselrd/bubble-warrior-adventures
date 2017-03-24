#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "EventQueue.hpp"
#include "State.hpp"

class StateHandler final : public std::enable_shared_from_this<StateHandler> {
public:
    void handleEvent(sf::Event& e);
    void update(float delta);
    void draw(sf::RenderWindow& window);
    template <class S, class... Args>
    void change(Args&&... args);
    template <class S, class... Args>
    void push(Args&&... args);
    void pop();
    void handleTransition();
    bool empty() const;
    std::size_t size() const;

private:
    enum class Event {
        Null,
        Change,
        Push,
        Pop
    };

    EventQueue<Event, std::shared_ptr<State>> _eventQueue;
    std::stack<std::shared_ptr<State>> _states;
};

#include "StateHandler.tpp"
