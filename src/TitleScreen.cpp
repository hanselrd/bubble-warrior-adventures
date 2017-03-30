#include "TitleScreen.hpp"
#include "Config.hpp"
#include "Locator.hpp"
#include "PlayScreen.hpp"
#include "ResourceHandler.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"

TitleScreen::TitleScreen(sf::RenderWindow& window) {
    _gui.setWindow(window);

    auto resourceHandler = Locator<ResourceHandler>::get();
    auto settings = Locator<Settings>::get();

    // Pulls the window dimensions from the window
    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    // Gets the default theme from the ResourceCache
    auto theme = resourceHandler->get<tgui::Theme>("default");

    // Background image
    auto background = tgui::Picture::create();
    background->setTexture(BACKGROUNDS_DIR + settings->getBackground());
    _gui.add(background);

    // Loads the font for the title
    auto titleFont = resourceHandler->emplace<sf::Font>("titleFont");
    titleFont->loadFromFile(FONTS_DIR + settings->getFont());

    // "Bubble Warrior" text component
    tgui::Label::Ptr lblTitle1 = theme->load("Label");
    lblTitle1->setFont(*titleFont);
    lblTitle1->setTextSize(72);
    lblTitle1->setTextColor(sf::Color::Black);
    lblTitle1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblTitle1->setSize(windowWidth, 500);
    lblTitle1->setPosition(0, windowHeight / 6);
    lblTitle1->setText("Bubble Warrior");
    _gui.add(lblTitle1);

    // "Adventures" text component
    tgui::Label::Ptr lblTitle2 = theme->load("Label");
    lblTitle2->setFont(*titleFont);
    lblTitle2->setTextSize(72);
    lblTitle2->setTextColor(sf::Color(0x001b0bff));
    lblTitle2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblTitle2->setSize(windowWidth, 500);
    lblTitle2->setPosition(0, windowHeight * 7 / 20);
    lblTitle2->setText("Adventures");
    _gui.add(lblTitle2);

    // Button constants
    constexpr unsigned BUTTON_HEIGHT = 50,
                       BUTTON_PADDING = 40;

    // Play button
    tgui::Button::Ptr btnPlay = theme->load("Button");
    btnPlay->setSize(windowWidth / 2 - BUTTON_PADDING, BUTTON_HEIGHT);
    btnPlay->setPosition(BUTTON_PADDING, windowHeight * 3 / 5);
    btnPlay->setText("Play");
    btnPlay->connect("pressed", [&] {
        auto stateHandler = Locator<StateHandler>::get();
        if (stateHandler->size() == 1)
            stateHandler->change<PlayScreen>(std::ref(window));
        else
            stateHandler->pop();
    });
    _gui.add(btnPlay);

    // Settings button
    tgui::Button::Ptr btnSettings = theme->load("Button");
    btnSettings->setSize(windowWidth / 2 - BUTTON_PADDING * 2, BUTTON_HEIGHT);
    btnSettings->setPosition(windowWidth / 2 + BUTTON_PADDING,
        windowHeight * 3 / 5);
    btnSettings->setText("Settings");
    _gui.add(btnSettings);

    // Credits button
    tgui::Button::Ptr btnCredits = theme->load("Button");
    btnCredits->setSize(windowWidth / 2 - BUTTON_PADDING, BUTTON_HEIGHT);
    btnCredits->setPosition(BUTTON_PADDING,
        windowHeight * 3 / 5 + BUTTON_HEIGHT + BUTTON_PADDING);
    btnCredits->setText("Credits");
    _gui.add(btnCredits);

    // Exit confirmation
    tgui::MessageBox::Ptr msgboxExit = theme->load("MessageBox");

    // Exit button
    tgui::Button::Ptr btnExit = theme->load("Button");
    btnExit->setSize(windowWidth / 2 - BUTTON_PADDING * 2, BUTTON_HEIGHT);
    btnExit->setPosition(windowWidth / 2 + BUTTON_PADDING,
        windowHeight * 3 / 5 + BUTTON_HEIGHT + BUTTON_PADDING);
    btnExit->setText("Exit");
    btnExit->connect("pressed", [=] {
        btnPlay->disable();
        btnSettings->disable();
        btnCredits->disable();
        btnExit->disable();
        auto msgboxExitOffset = msgboxExit->getSizeLayout() / 2;
        msgboxExit->setPosition(windowWidth / 2 - msgboxExitOffset.x,
            windowHeight / 2 - msgboxExitOffset.y);
        msgboxExit->show();
    });
    _gui.add(btnExit);

    // Exit confirmation continued
    msgboxExit->setTitle("Exit Confirmation");
    msgboxExit->setText("Are you sure you want to exit?");
    msgboxExit->addButton("Yes");
    msgboxExit->addButton("No");
    msgboxExit->hide();
    msgboxExit->connect("buttonpressed", [=, &window](const std::string& text) {
        if (text == "Yes")
            window.close();
        else if (text == "No") {
            btnPlay->enable();
            btnSettings->enable();
            btnCredits->enable();
            btnExit->enable();
        }
        msgboxExit->hide();
    });
    msgboxExit->connect("closed", [=] {
        btnPlay->enable();
        btnSettings->enable();
        btnCredits->enable();
        btnExit->enable();
        msgboxExit->hide();
    });
    _gui.add(msgboxExit);
}

void TitleScreen::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void TitleScreen::update(float delta) {
}

void TitleScreen::draw(sf::RenderWindow& window) {
    _gui.draw();
}
