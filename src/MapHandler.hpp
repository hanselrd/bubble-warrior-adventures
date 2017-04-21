#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Camera.hpp"

class MapHandler final : public std::enabled_shared_from_this<MapHandler> {
public:


private:
    Camera _camera;
};
