#pragma once
#include <boost/any.hpp>
#include <memory>
#include <string>
#include <unordered_map>

struct ResourceHandler final {
    template <class T, class... Args>
    static void emplace(const std::string& key, Args&&... args);
    static void remove(const std::string& key);
    static bool exists(const std::string& key);
    template <class T>
    static std::shared_ptr<T> get(const std::string& key);

private:
    static std::unordered_map<std::string, boost::any> _cache;
};

#include "ResourceHandler.tpp"
