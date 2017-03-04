#pragma once
#include <memory>
#include <stdexcept>
#include <string>

template <class T>
struct Locator final {
    static inline void provide(T* t) {
        _service.reset(t);
    }

    static inline T* get() {
        if (!_service)
            throw std::runtime_error(std::string("_service in ") + typeid(T).name() + "is NULL");
        return _service.get();
    }

private:
    static std::unique_ptr<T> _service;
};

template <typename T>
std::unique_ptr<T> Locator<T>::_service;
