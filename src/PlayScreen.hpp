#pragma once
#include "State.hpp"
#include "Tmx.hpp"

class PlayScreen final : public State {
public:
    explicit PlayScreen(StateHandler& stateHandler, sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::CircleShape _player;
    sf::View _view;
    tmx::Map _map; // for testing
};
