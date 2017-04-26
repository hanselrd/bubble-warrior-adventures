#pragma once
#include "State.hpp"

class CreditsScreen final : public State {
public:
    explicit CreditsScreen(sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;
};
