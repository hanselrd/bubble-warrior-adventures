#pragma once
#include "GameState.hpp"
#include "Tmx.hpp"

class PlayState final : public GameState {
public:
    explicit PlayState(StateHandler& stateHandler, sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::CircleShape _player;
    sf::View _view;
    tmx::Map _map; // for testing
};
