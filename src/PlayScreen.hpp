#pragma once
#include "Player.hpp"
#include "Map.hpp"
#include "State.hpp"

class PlayScreen final : public State {
public:
    explicit PlayScreen(sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;

    void initializeOverlay(sf::RenderWindow &window);
    void updateOverlay();
private:
    sf::View _view;
    Map _map; // for testing
    Player _player;
    sf::Clock _overlayUpdate;
};
