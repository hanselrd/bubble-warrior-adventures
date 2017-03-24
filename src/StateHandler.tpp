#include <functional>

template <class S, class... Args>
void StateHandler::change(Args&&... args) {
    _eventQueue.notify(Event::Change, std::make_shared<S>(std::forward<Args>(args)...));
}

template <class S, class... Args>
void StateHandler::push(Args&&... args) {
    _eventQueue.notify(Event::Push, std::make_shared<S>(std::forward<Args>(args)...));
}
