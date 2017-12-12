#pragma once
#include "Object.hpp"

class Item final : public Object {
public:
    Item();
    Item(std::string file_path, int sprite_format);
    Item(std::string file_path, int sprite_format, std::string name, int level, int health, int mana, int damage, float movement, float armor, float current_exp, float max_exp);
    sf::FloatRect getLocalBounds() const override;

    int getItemLevel() const;
    int getHealth() const;
    int getMana() const;
    int getDamage() const;
    float getMovementSpeed() const;
    float getArmor() const;
    float getCurrentItemExperience() const;
    float getMaxItemExperience() const;
    std::string getName() const;

    void setItemLevel(int item_level);
    void setHealth(int health);
    void setMana(int mana);
    void setDamage(int damage);
    void setMovementSpeed(float movement_speed);
    void setArmor(float armor);
    void setCurrentItemExperience(float current_exp);
    void setMaxItemExperience(float max_exp);
    void setName(std::string name);

    void shatter();
    void loadItem(std::string file_name, int sprite_format, std::string name, int level, int health, int mana, int damage, float movement, float armor, float current_exp, float max_exp);

private:
    int _itemLevel;
    int _health, _mana, _damage;
    int _spriteFormat;
    float _currentItemExperience, _maxItemExperience;
    float _movementSpeed, _armor;

    std::string _name;

    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::IntRect _intRect;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};