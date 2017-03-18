#include <stdexcept>
#include <string>

template <class T>
std::unique_ptr<T> Locator<T>::_service;

template <class T>
void Locator<T>::provide(T* t) {
    _service.reset(t);
}

template <class T>
T* Locator<T>::get() {
    if (!_service)
        throw std::runtime_error(std::string("_service in ") + typeid(T).name() + " is NULL");
    return _service.get();
}
