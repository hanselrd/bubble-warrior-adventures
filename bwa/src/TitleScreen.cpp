#include "TitleScreen.hpp" // Relative header
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "ResourceLoader.hpp"

/*
	Default constructor for TitleScreen.
	Loads all gui components.
*/
bwa::TitleScreen::TitleScreen(sf::RenderWindow &window) {
	_gui.setWindow(window);
	bwa::TitleScreen::loadDrawables(_gui);
}

/*
	Overloads parent draw() function. Draws the gui components
*/
void bwa::TitleScreen::draw(sf::RenderWindow &window) {
	_gui.draw();
}

/*
	Handles gui event based on _gui's connect() function components
*/
void bwa::TitleScreen::handleEvents(sf::Event &e) {
	_gui.handleEvent(e);
}

/*
	To be implemented
*/
void bwa::TitleScreen::update(float delta) {

}

/*
	Loads all gui components, sets their display,
	and sets up mouse events with respect to _gui components
*/
void bwa::TitleScreen::loadDrawables(tgui::Gui &gui) {
	// Pulls the window dimmensions from the window
	auto window_width = tgui::bindWidth(gui);
	auto window_height = tgui::bindHeight(gui);

	// To be used for the background of the window
	tgui::Picture::Ptr background = std::make_shared<tgui::Picture>();
	gui.add(background);

	// "Bubble Warrior" text component
	tgui::Label::Ptr title = std::make_shared<tgui::Label>();
	title->setTextSize(72);
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title->setSize(window_width, 500);
	title->setPosition(0, window_height/5);
	title->setText("Bubble Warrior");
	title->setTextColor(sf::Color::Green);
	gui.add(title);

	// "Adventures" text component
	tgui::Label::Ptr title2 = std::make_shared<tgui::Label>();
	title2->setTextSize(72);
	title2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title2->setSize(window_width, 500);
	title2->setPosition(0, window_height * 7/20);
	title2->setText("Adventures");
	title2->setTextColor(sf::Color::Green);
	gui.add(title2);

	// "Click to continue" text component
	tgui::Label::Ptr click_to_continue = std::make_shared<tgui::Label>();
	click_to_continue->setTextSize(38);
	click_to_continue->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	click_to_continue->setSize(window_width,100);
	click_to_continue->setPosition(0, window_height * 3 / 4);
	click_to_continue->setText("Click or press Enter to continue");
	click_to_continue->setTextColor(sf::Color::White);
	gui.add(click_to_continue);
}