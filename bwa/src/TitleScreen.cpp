#include <TGUI/TGUI.hpp>
#include <memory>
#include "ResourceLoader.hpp"
#include "TitleScreen.hpp"


bwa::TitleScreen::TitleScreen() {
	int x = 0;
}

void bwa::TitleScreen::draw(sf::RenderWindow & window) {
	tgui::Gui gui(window);
	bwa::TitleScreen::loadDrawables(gui);
	gui.draw();
}

void bwa::TitleScreen::handleEvents(sf::Event & e) {
}

void bwa::TitleScreen::update(float delta){
}

void bwa::TitleScreen::loadDrawables(tgui::Gui & gui) {
	auto window_width = tgui::bindWidth(gui);
	auto window_height = tgui::bindHeight(gui);
	// Need help making this next line work with ResourceLoader.cpp
	tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>("dependencies/TGUI-0.7/widgets/black.txt");

	tgui::Button::Ptr continue_button = theme->load("Button");
	continue_button->setText("Continue");
	continue_button->setSize(window_width * 2 / 3, window_height / 8);
	continue_button->setPosition(window_width / 6, window_height / 6);
	gui.add(continue_button, "Play_Button");

	tgui::Button::Ptr new_game_button = theme->load("Button");
	new_game_button->setText("New Game");
	new_game_button->setSize(window_width * 2 / 3, window_height / 8);
	new_game_button->setPosition(window_width / 6, window_height * 2 / 6);
	gui.add(new_game_button, "new_game_Button");

	tgui::Button::Ptr options_button = theme->load("Button");
	options_button->setText("Options");
	options_button->setSize(window_width * 2 / 3, window_height / 8);
	options_button->setPosition(window_width / 6, window_height * 3 / 6);
	gui.add(options_button, "options_button");

	tgui::Button::Ptr exit_button = theme->load("Button");
	exit_button->setText("Quit");
	exit_button->setSize(window_width * 2 / 3, window_height / 8);
	exit_button->setPosition(window_width / 6, window_height * 4 / 6);
	exit_button->connect("pressed", &TitleScreen::buttonClicked, this, "exit");
	gui.add(exit_button, "exit_button");

}

void bwa::TitleScreen::buttonClicked(std::string s) {
	std::cout << "Exiting" << std::endl;
	if (!s.compare("exit")) {
	}
}
