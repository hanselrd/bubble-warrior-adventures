#pragma once
#include "Object.hpp"
#include "Map.hpp"

class InvisibleBarrier final: public Object {
public:
    InvisibleBarrier(Map::Object mapObject);
    sf::FloatRect getLocalBounds() const override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    //unsigned int _x, _y, _width, _height;

};