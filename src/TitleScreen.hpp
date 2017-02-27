#pragma once
#include "GameState.hpp"

class TitleScreen final : public GameState {
public:
    explicit TitleScreen(StateHandler& stateHandler, sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;
};
