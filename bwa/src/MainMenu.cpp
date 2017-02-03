#include <TGUI/TGUI.hpp>
#include <memory>
#include "MainMenu.hpp"
#include "ResourceLoader.hpp"

/*
	Basic constructor for MainMenu class.
*/
bwa::MainMenu::MainMenu() {
}

/*
	Overrides parent class's draw function.
	Draws the gui of the main menu, and the visuals for
	the entire screen
*/
void bwa::MainMenu::draw(sf::RenderWindow & window) {
	tgui::Gui gui(window);
	bwa::MainMenu::loadDrawables(gui);
	gui.draw();
}

void bwa::MainMenu::handleEvents(sf::Event & e) {
}

void bwa::MainMenu::update(float delta) {
}

/*
	Helper function to add components to gui for the
	draw() function. All components are stored in gui
	so that gui.draw() will show all components
*/
void bwa::MainMenu::loadDrawables(tgui::Gui & gui) {
	auto window_width = tgui::bindWidth(gui);
	auto window_height = tgui::bindHeight(gui);
	// Need help making this next line work with ResourceLoader.cpp
	tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>("dependencies/TGUI-0.7/widgets/black.txt");

	// Creates and formats the Continue Button
	tgui::Button::Ptr continue_button = theme->load("Button");
	continue_button->setText("Continue");
	continue_button->setSize(window_width * 2 / 3, window_height / 8);
	continue_button->setPosition(window_width / 6, window_height / 6);
	gui.add(continue_button, "Play_Button");

	// Creates and formats the New Game button
	tgui::Button::Ptr new_game_button = theme->load("Button");
	new_game_button->setText("New Game");
	new_game_button->setSize(window_width * 2 / 3, window_height / 8);
	new_game_button->setPosition(window_width / 6, window_height * 2 / 6);
	gui.add(new_game_button, "new_game_Button");

	// Creates and formats the Options button
	tgui::Button::Ptr options_button = theme->load("Button");
	options_button->setText("Options");
	options_button->setSize(window_width * 2 / 3, window_height / 8);
	options_button->setPosition(window_width / 6, window_height * 3 / 6);
	gui.add(options_button, "options_button");

	// Creates and formats the Exit button
	tgui::Button::Ptr exit_button = theme->load("Button");
	exit_button->setText("Quit");
	exit_button->setSize(window_width * 2 / 3, window_height / 8);
	exit_button->setPosition(window_width / 6, window_height * 4 / 6);
	gui.add(exit_button, "exit_button");

	// Handles button actions
	exit_button->connect("pressed", &MainMenu::buttonClicked, this, "exit");
}

/*
	Helper function to change bwa::Game's stack to the
	next gamestate, integrating it with the Main Menu's
	buttons
*/
void bwa::MainMenu::buttonClicked(std::string s) {
	// ***** not all options coded yet
	if (!s.compare("exit")) {
		// ***** Insert code to change the Game class's stack to include exiting
	}
}
