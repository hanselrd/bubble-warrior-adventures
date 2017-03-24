#include <utility>

template <class E, class D>
void EventQueue<E, D>::notify(const E& event, const D& data) {
    _events.push(std::make_tuple(event, data));
}

template <class E, class D>
bool EventQueue<E, D>::poll(E& event, D& data) {
    if (_events.empty())
        return false;

    const auto& front = _events.front();
    event = std::get<0>(front);
    data = std::get<1>(front);
    _events.pop();
    return true;
}
