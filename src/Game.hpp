#pragma once
#include <TGUI/TGUI.hpp>
#include <memory>
#include "ResourceHandler.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"

class Game final {
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow _window;
    tgui::Gui _gui;
    std::shared_ptr<ResourceHandler> _resourceHandler;
    std::shared_ptr<Settings> _settings;
    std::shared_ptr<StateHandler> _stateHandler;
};
