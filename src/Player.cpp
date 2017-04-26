#include "Player.hpp"
#include <cmath>

Player::Player()
    : Entity(8, sf::Color(0xFF9900FF)) {}

void Player::handleEvent(sf::Event& e) {}

void Player::update(float delta) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move(0, -70 * delta);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move(-70 * delta, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move(0, 70 * delta);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move(70 * delta, 0);
}
