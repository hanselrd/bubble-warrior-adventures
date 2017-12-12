#pragma once
#include <memory>
#include <vector>
#include "Camera.hpp"
#include "MapHandler.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "State.hpp"
#include "NPC.hpp"

class PlayScreen final : public State {
public:
    explicit PlayScreen(sf::RenderWindow& window);
    void handleEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;

    std::vector<std::shared_ptr<NPC>>& PlayScreen::getNPCs();
    std::vector<std::shared_ptr<Object>>& PlayScreen::getObjects();
    std::vector<std::shared_ptr<Item>>& PlayScreen::getItems();
    std::vector<std::shared_ptr<Enemy>>& PlayScreen::getEnemies();

    void reloadObjects(Entity::EntityType type);
    void updateOverlay();
private:
    Camera _camera;
    Map _map; // Testing (should use a MapHandler)
    Player _player;
    std::vector<std::shared_ptr<Enemy>> _enemies;
    std::vector<std::shared_ptr<Object>> _objects;
    std::vector<std::shared_ptr<Item>> _items;
    std::vector<std::shared_ptr<NPC>> _npcs;
    sf::Clock _overlayUpdate;
    std::shared_ptr<MapHandler> _mapHandler;
};
