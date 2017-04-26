#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation final {
public:
    void addFrame(sf::IntRect rect);
    void setSpriteSheet(const sf::Texture& texture);
    const sf::Texture* getSpriteSheet() const;
    std::size_t getSize() const;
    sf::IntRect getFrame(std::size_t n) const;

private:
    std::vector<sf::IntRect> _frames;
    const sf::Texture* _texture = nullptr;
};
