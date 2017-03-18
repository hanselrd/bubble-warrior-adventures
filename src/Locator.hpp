#pragma once
#include <memory>

template <class T>
struct Locator final {
    static void provide(const std::shared_ptr<T>& ptr);
    static std::shared_ptr<T> get();

private:
    static std::weak_ptr<T> _service;
};

#include "Locator.tpp"
