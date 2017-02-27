#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class StateHandler;

class GameState {
public:
    explicit GameState(StateHandler& stateHandler);
    virtual void handleEvent(sf::Event& e) = 0;
    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void pause();
    virtual void resume();

protected:
    tgui::Gui _gui;
    StateHandler& _stateHandler;
};
