#pragma once
#include <boost/any.hpp>
#include <queue>
#include <tuple>
#include <type_traits>

template <class T, class E>
class EventQueue {
public:
    void pollEvent(const E& e, const boost::any& data);

private:
    std::queue<std::tuple<E, boost::any>> _events;
};
