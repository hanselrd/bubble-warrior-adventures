#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

template <typename T>
struct ResourceCache final {
    /*
        Creates a resource with the arguments passed in and
        stores it in the cache under the string 'key'. If 'key'
        is already taken then it will overwrite it.
    */
    template <typename... Args>
    static inline std::shared_ptr<T> create(const std::string& key, Args&&... args) {
        auto res = std::make_shared<T>(std::forward<Args>(args)...);
        _cache.insert(std::make_pair(key, res));
        return std::move(res);
    }

    /*
        Checks if a resource exists under the string 'key'.
    */
    static inline bool exists(const std::string& key) {
        return _cache.count(key) != 0;
    }

    /*
        Gets a resource under the string 'key'. If it doesn't exist,
        an exception is thrown.
    */
    static inline std::shared_ptr<T> get(const std::string& key) {
        if (!exists(key))
            throw std::runtime_error("Could not get: '" + key + "'" + " as '" + typeid(T).name() + "'");
        return _cache.at(key);
    }

private:
    static std::map<std::string, std::shared_ptr<T>> _cache;
};

template <typename T>
std::map<std::string, std::shared_ptr<T>> ResourceCache<T>::_cache;
