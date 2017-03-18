#pragma once
#include <memory>

template <class T>
struct Locator final {
    static void provide(T* t);
    static T* get();

private:
    static std::unique_ptr<T> _service;
};

#include "Locator.tpp"
