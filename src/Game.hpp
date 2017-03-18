#pragma once
#include <TGUI/TGUI.hpp>
#include <memory>
#include <string>
#include "StateHandler.hpp"

class Game final {
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow _window;
    tgui::Gui _gui;
    StateHandler _stateHandler;
};
