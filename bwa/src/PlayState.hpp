#pragma once
#include "GameState.hpp"

class PlayState final : public GameState {
public:
	explicit PlayState(StateHandler& stateHandler, sf::RenderWindow& window);
	PlayState(const PlayState&) = delete;
	PlayState& operator=(const PlayState&) = delete;

	void handleEvent(sf::Event& e) override;
	void update(float delta) override;
	void draw(sf::RenderWindow& window) override;

private:
	sf::RectangleShape _rect;
	sf::View _view;
};
