#include "CreditsScreen.hpp"
#include "Config.hpp"
#include "Locator.hpp"
#include "ResourceHandler.hpp"
#include "Settings.hpp"
#include "StateHandler.hpp"

CreditsScreen::CreditsScreen(sf::RenderWindow& window) {
    _gui.setWindow(window);

    auto resourceHandler = Locator<ResourceHandler>::get();
    auto settings = Locator<Settings>::get();

    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    auto theme = resourceHandler->get<tgui::Theme>(THEME_DEFAULT);

    auto background = tgui::Picture::create();
    background->setTexture(BACKGROUNDS_DIR + settings->getBackground());
    _gui.add(background);

    const sf::Color CREDITS_COLOR = sf::Color::Black;

    tgui::Label::Ptr lblHansel = theme->load("Label");
    lblHansel->setTextSize(60);
    lblHansel->setTextColor(CREDITS_COLOR);
    lblHansel->setTextStyle(sf::Text::Bold);
    lblHansel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblHansel->setSize(windowWidth, 70);
    lblHansel->setPosition(0, windowHeight * 2 / 10);
    lblHansel->setText("Hansel De La Cruz");
    _gui.add(lblHansel);

    tgui::Label::Ptr lblHanselTitle = theme->load("Label");
    lblHanselTitle->setTextSize(25);
    lblHanselTitle->setTextColor(CREDITS_COLOR);
    lblHanselTitle->setTextStyle(sf::Text::Bold);
    lblHanselTitle->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblHanselTitle->setSize(windowWidth, 30);
    lblHanselTitle->setPosition(0, lblHansel->getPosition().y + lblHansel->getFullSize().y);
    lblHanselTitle->setText("Lead Developer");
    _gui.add(lblHanselTitle);

    tgui::Label::Ptr lblKyle = theme->load("Label");
    lblKyle->setTextSize(60);
    lblKyle->setTextColor(CREDITS_COLOR);
    lblKyle->setTextStyle(sf::Text::Bold);
    lblKyle->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblKyle->setSize(windowWidth, 70);
    lblKyle->setPosition(0, windowHeight * 4 / 10);
    lblKyle->setText("Kyle Jolicoeur");
    _gui.add(lblKyle);

    tgui::Label::Ptr lblKyleTitle = theme->load("Label");
    lblKyleTitle->setTextSize(25);
    lblKyleTitle->setTextColor(CREDITS_COLOR);
    lblKyleTitle->setTextStyle(sf::Text::Bold);
    lblKyleTitle->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblKyleTitle->setSize(windowWidth, 30);
    lblKyleTitle->setPosition(0, lblKyle->getPosition().y + lblKyle->getFullSize().y);
    lblKyleTitle->setText("Developer");
    _gui.add(lblKyleTitle);

    tgui::Label::Ptr lblJennifer = theme->load("Label");
    lblJennifer->setTextSize(60);
    lblJennifer->setTextColor(CREDITS_COLOR);
    lblJennifer->setTextStyle(sf::Text::Bold);
    lblJennifer->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblJennifer->setSize(windowWidth, 70);
    lblJennifer->setPosition(0, windowHeight * 6 / 10);
    lblJennifer->setText("Jennifer Green");
    _gui.add(lblJennifer);

    tgui::Label::Ptr lblJenniferTitle = theme->load("Label");
    lblJenniferTitle->setTextSize(25);
    lblJenniferTitle->setTextColor(CREDITS_COLOR);
    lblJenniferTitle->setTextStyle(sf::Text::Bold);
    lblJenniferTitle->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    lblJenniferTitle->setSize(windowWidth, 30);
    lblJenniferTitle->setPosition(0, lblJennifer->getPosition().y + lblJennifer->getFullSize().y);
    lblJenniferTitle->setText("Designer");
    _gui.add(lblJenniferTitle);

    tgui::Button::Ptr btnMainMenu = theme->load("Button");
    btnMainMenu->setSize(windowWidth / 5, 50);
    btnMainMenu->setPosition(windowWidth / 2 - btnMainMenu->getFullSize().x / 2, windowHeight * 8 / 10);
    btnMainMenu->setText("Main Menu");
    btnMainMenu->connect("pressed", [] {
        Locator<StateHandler>::get()->pop();
    });
    _gui.add(btnMainMenu);
}

void CreditsScreen::handleEvent(sf::Event& e) {
    _gui.handleEvent(e);
}

void CreditsScreen::update(float delta) {}

void CreditsScreen::draw(sf::RenderWindow& window) {
    _gui.draw();
}
