#pragma once
#include "State.hpp"

class TitleScreen final : public State {
public:
    explicit TitleScreen(sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;
};
