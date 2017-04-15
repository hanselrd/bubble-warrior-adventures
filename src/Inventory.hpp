#pragma once
#include "Item.hpp"

class Inventory {
public:
    Inventory();

    void addItem(Item &item);
    void removeItem(Item &item);
    Item getItem(int i);

    bool contains(Item &item);
    void drawInventory(sf::RenderWindow &window);
    void handleEvents(sf::Event &e);
private:
    std::vector<Item> _items;

};