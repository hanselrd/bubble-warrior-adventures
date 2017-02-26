#pragma once
#include "GameState.hpp"

class PlayState final : public GameState {
public:
	explicit PlayState(StateHandler& stateHandler, sf::RenderWindow& window);
	void handleEvent(sf::Event& e) override;
	void update(float delta) override;
	void draw(sf::RenderWindow& window) override;

private:
	sf::RectangleShape _box;
	sf::CircleShape _player;
	sf::View _view;
};
