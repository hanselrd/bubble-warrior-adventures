#pragma once
#include <queue>
#include <tuple>

template <class E, class D>
class EventQueue final {
public:
    void notify(const E& event, const D& data);
    bool poll(E& event, D& data);

private:
    std::queue<std::tuple<E, D>> _events;
};

#include "EventQueue.tpp"
