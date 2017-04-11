#include <string>
#include <utility>
#include "game.hpp"

constexpr const char* WINDOW_TITLE = "Bubble Warrior Adventures!";

bwa::Game::Game() {
	_lua.script_file("config.lua");
	sol::table resolution = _lua["resolution"];
	_font.loadFromFile(_lua["game_fonts"]["normal"]);
	_text.setFont(_font);
	_text.setFillColor(sf::Color::Yellow);
	_text.setString("FPS:");
	auto xy = std::make_pair(
		resolution["x"].get<unsigned>(), 
		resolution["y"].get<unsigned>());
	if (_lua["fullscreen"].get<bool>())
		_window.create({ xy.first, xy.second }, WINDOW_TITLE,
			sf::Style::Fullscreen);
	else
		_window.create({ xy.first, xy.second }, WINDOW_TITLE);
	_window.setVerticalSyncEnabled(true);
	_gui.setWindow(_window);
}

void bwa::Game::run() {
	sf::Clock clock, update_fps;
	float last_time = 0.f, current_time, fps;
	bool show_fps_counter = _lua["show_fps_counter"];
	sf::Texture texture;
	sf::IntRect heroRect(0, (64 * 8), (64), (64));
	texture.loadFromFile("assets/sprites/golden_hero_female_no_shield.png");
	sf::Sprite heroSprite(texture, heroRect);
	heroSprite.setPosition(400, 400);
	sf::Clock clock2;

	while (_window.isOpen()) {
		sf::Event e;
		while (_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_window.close();
			_gui.handleEvent(e);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				heroRect.top = (64 * 8);
				heroSprite.move(0, -5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				heroRect.top = (64 * 9);
				heroSprite.move(-5, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				heroRect.top = (64 * 10);
				heroSprite.move(0, 5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				heroRect.top = (64 * 11);
				heroSprite.move(5, 0);
			}
		}
		// calculates fps
		if (show_fps_counter) {
			current_time = clock.restart().asSeconds();
			fps = 1.f / (current_time - last_time);
			if (update_fps.getElapsedTime() > sf::seconds(1.f)) {
				_text.setString("FPS: " + std::to_string(unsigned(fps)));
				update_fps.restart();
			}
		}
		if (clock2.getElapsedTime().asSeconds() > 0.1f) {
			if (heroRect.left == ((64*1) * 8))
				heroRect.left = 0;
			else heroRect.left += (64*1);
			heroSprite.setTextureRect(heroRect);
			clock2.restart();
		}

		_window.clear();
		_gui.draw();
		

		_window.draw(heroSprite);
		// displays fps if show_fps_counter is true
		if (show_fps_counter)
			_window.draw(_text);
		_window.display();
	}
}
