#pragma once
#include <boost/any.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class ResourceHandler final : public std::enable_shared_from_this<ResourceHandler> {
public:
    template <class T, class... Args>
    std::shared_ptr<T> emplace(const std::string& key, Args&&... args);
    void remove(const std::string& key);
    bool exists(const std::string& key);
    template <class T>
    std::shared_ptr<T> get(const std::string& key);

private:
    std::unordered_map<std::string, boost::any> _cache;
};

#include "ResourceHandler.tpp"
