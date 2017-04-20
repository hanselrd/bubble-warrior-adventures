#pragma once
#include "Map.hpp"
#include "Player.hpp"
#include "State.hpp"

class PlayScreen final : public State {
public:
    explicit PlayScreen(sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::View _view;
    Map _map; // Testing (should use a MapHandler)
    Player _player;
};
