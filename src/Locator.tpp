#include <stdexcept>
#include <string>

template <class T>
std::weak_ptr<T> Locator<T>::_service;

template <class T>
void Locator<T>::provide(const std::shared_ptr<T>& ptr) {
    _service = ptr;
}

template <class T>
std::shared_ptr<T> Locator<T>::get() {
    if (auto ptr = _service.lock())
        return ptr;
    else
        throw std::runtime_error(std::string(typeid(T).name()) + "'s _service is empty");
}
