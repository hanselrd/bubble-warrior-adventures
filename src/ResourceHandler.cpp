#include "ResourceHandler.hpp"

std::unordered_map<std::string, boost::any> ResourceHandler::_cache;

void ResourceHandler::remove(const std::string& key) {
    if (exists(key))
        _cache.erase(key);
}

bool ResourceHandler::exists(const std::string& key) {
    return _cache.count(key) != 0;
}
