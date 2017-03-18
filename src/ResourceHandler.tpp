#include <functional>

template <class T, class... Args>
std::shared_ptr<T> ResourceHandler::emplace(const std::string& key, Args&&... args) {
    auto res = std::make_shared<T>(std::forward<Args>(args)...);
    _cache.insert(std::make_pair(key, res));
    return get<T>(key);
}

template <class T>
std::shared_ptr<T> ResourceHandler::get(const std::string& key) {
    if (!exists(key))
        return nullptr;
    auto res = boost::any_cast<std::shared_ptr<T>>(_cache.at(key));
    return res;
}
