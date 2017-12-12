#pragma once
#include <memory>
#include <vector>
#include "Camera.hpp"
#include "MapHandler.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "State.hpp"

class PlayScreen final : public State {
public:
    explicit PlayScreen(sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;

    const std::vector<Entity>& PlayScreen::getNPCs() const;

    void updateOverlay();
private:
    Camera _camera;
    Map _map; // Testing (should use a MapHandler)
    Player _player;
    std::vector<std::shared_ptr<Entity>> _entities;
    sf::Clock _overlayUpdate;
    std::shared_ptr<MapHandler> _mapHandler;
};
