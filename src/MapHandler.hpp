#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include "Map.hpp"

class MapHandler final : public std::enable_shared_from_this<MapHandler> {
public:
    void someFunc() {} // remove

private:
    std::unordered_map<std::string, Map> _maps;
};
