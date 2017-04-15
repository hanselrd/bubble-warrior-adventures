#include "Item.hpp"

Item::Item() {
    _name = "null";
    _spriteFormat = 32;
    _itemLevel = 0;
    _health = 0;
    _damage = 0;
    _mana = 0;
    _movementSpeed = 1.0f;
    _armor = 0.0f;
    _currentItemExperience = 0.0f;
    _maxItemExperience = 0.0f;
}

Item::Item(std::string file_path, int sprite_format) {
    _texture.loadFromFile("assets/sprites/" + file_path);
    _sprite.setTexture(_texture);
    _spriteFormat = sprite_format;    
    _intRect = sf::IntRect(0, 0 , sprite_format, sprite_format);
    _sprite.setTextureRect(_intRect);

    _name = "null";
    _itemLevel = 0;
    _damage = 0;
    _health = 0;
    _mana = 0;
    _movementSpeed = 1.0f;
    _armor = 0.0f;
    _currentItemExperience = 0.0f;
    _maxItemExperience = 0.0f;
}

Item::Item(std::string file_path, int sprite_format, std::string name, int level, int health, int mana, int damage, float movement, float armor, float current_exp, float max_exp) {
    _texture.loadFromFile("assets/sprites/" + file_path);
    _sprite.setTexture(_texture);
    _spriteFormat = sprite_format;
    _intRect = sf::IntRect(0, 0, sprite_format, sprite_format);
    _sprite.setTextureRect(_intRect);

    _name = name;
    _itemLevel = level;
    _health = health;
    _mana = mana;
    _damage = damage;
    _movementSpeed = movement;
    _armor = armor;
    _currentItemExperience = current_exp;
    _maxItemExperience = max_exp;
}
// Setters and Getters
std::string Item::getName() {
    return _name;
}
int Item::getItemLevel() {
    return _itemLevel;
}
int Item::getHealth() {
    return _health;
}
int Item::getMana() {
    return _mana;
}
int Item::getDamage() {
    return _damage;
}
float Item::getMovementSpeed() {
    return _movementSpeed;
}
float Item::getArmor() {
    return _armor;
}
float Item::getCurrentItemExperience() {
    return _currentItemExperience;
}
float Item::getMaxItemExperience() {
    return _maxItemExperience;
}
void Item::setName(std::string name) {
    _name = name;
}
void Item::setItemLevel(int item_level) {
    _itemLevel = item_level;
}
void Item::setHealth(int health) {
    _health = health;
}
void Item::setMana(int mana) {
    _mana = mana;
}
void Item::setDamage(int damage) {
    _damage = damage;
}
void Item::setMovementSpeed(float movement_speed) {
    _movementSpeed = movement_speed;
}
void Item::setArmor(float armor) {
    _armor = armor;
}
void Item::setCurrentItemExperience(float current_exp) {
    _currentItemExperience = current_exp;
}
void Item::setMaxItemExperience(float max_exp) {
    _maxItemExperience = max_exp;
}
void Item::shatter() {
    _itemLevel += 1;
    _health =  std::ceil(_health * 1.5f);
    _mana = std::ceil(_mana * 1.5f);
    _damage = std::ceil(_damage * 1.5f);
    _movementSpeed = _movementSpeed * 1.3f;
    _armor = _armor * 1.5f;
}
void Item::loadItem(std::string file_path, int sprite_format, std::string name, int level, int health, int mana, int damage, float movement, float armor, float current_exp, float max_exp) {
    _texture.loadFromFile("assets/sprites/" + file_path);
    _sprite.setTexture(_texture);
    _spriteFormat = sprite_format;
    _intRect = sf::IntRect(0, 0, sprite_format, sprite_format);
    _sprite.setTextureRect(_intRect);

    _name = name;
    _itemLevel = level;
    _health = health;
    _mana = mana;
    _damage = damage;
    _movementSpeed = movement;
    _armor = armor;
    _currentItemExperience = current_exp;
    _maxItemExperience = max_exp;
}
// Needed for other classes
void Item::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &_texture;
    target.draw(_sprite, states);
}

sf::FloatRect Item::getLocalBounds() const {
    return _sprite.getLocalBounds();
}