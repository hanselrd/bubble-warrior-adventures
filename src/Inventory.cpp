#include "Inventory.hpp"

Inventory::Inventory() {
}

void Inventory::addItem(Item &item) {
    _items.push_back(item);
}
void Inventory::removeItem(Item &item) {
    std::vector<Item> temp = _items;
    for (int j = 0; j < _items.size(); j++) {
        if (item.getName() != _items.at(j).getName()) {
            temp.push_back(_items.at(j));
        }
    }
    _items = temp;
}
Item Inventory::getItem(int i) {
    return _items.at(i);
}
// Inventory::contains would only be used for quest items hopefully
bool Inventory::contains(Item &item) {
    bool temp = false;
    for (int i = 0; i < _items.size(); i++) {
        if (_items.at(i).getName() == item.getName()) {
            temp = true;
        }
    }
}
void Inventory::handleEvents(sf::Event &e) {

}
void Inventory::drawInventory(sf::RenderWindow &window) {

}