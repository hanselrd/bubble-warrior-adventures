#include <functional>

template <class S, class... Args>
void StateHandler::change(Args&&... args) {
    helper<S>(Event::Change, std::forward<Args>(args)...);
}

template <class S, class... Args>
void StateHandler::push(Args&&... args) {
    helper<S>(Event::Push, std::forward<Args>(args)...);
}

template <class S, class... Args>
void StateHandler::helper(const Event e, Args&&... args) {
    _temp = std::make_unique<S>(std::ref(*this), std::forward<Args>(args)...);
    _event = e;
}
