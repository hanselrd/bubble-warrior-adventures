#include "TitleScreen.hpp" // Relative header
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "ResourceLoader.hpp"

/*
	Default constructor for TitleScreen
*/
bwa::TitleScreen::TitleScreen(sf::RenderWindow &window) {
	_gui.setWindow(window);
	bwa::TitleScreen::loadDrawables(_gui);
}
void bwa::TitleScreen::draw(sf::RenderWindow &window) {
	_gui.draw();
}
void bwa::TitleScreen::handleEvents(sf::Event &e) {
	_gui.handleEvent(e);
}
void bwa::TitleScreen::update(float delta) {

}
void bwa::TitleScreen::loadDrawables(tgui::Gui &gui) {
	auto window_width = tgui::bindWidth(gui);
	auto window_height = tgui::bindHeight(gui);

	tgui::Label::Ptr title = std::make_shared<tgui::Label>();
	title->setTextSize(72);
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title->setSize(window_width, 500);
	title->setPosition(0, window_height/5);
	title->setText("Bubble Warrior");
	title->setTextColor(sf::Color::Green);
	gui.add(title);

	tgui::Label::Ptr title2 = std::make_shared<tgui::Label>();
	title2->setTextSize(72);
	title2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title2->setSize(window_width, 500);
	title2->setPosition(0, window_height * 7/20);
	title2->setText("Adventures");
	title2->setTextColor(sf::Color::Green);
	gui.add(title2);

	tgui::Label::Ptr click_to_continue = std::make_shared<tgui::Label>();
	click_to_continue->setTextSize(38);
	click_to_continue->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	click_to_continue->setSize(window_width,100);
	click_to_continue->setPosition(0, window_height * 3 / 4);
	click_to_continue->setText("Click or press Enter to continue");
	click_to_continue->setTextColor(sf::Color::White);
	gui.add(click_to_continue);
}
