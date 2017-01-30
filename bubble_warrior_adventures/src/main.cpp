#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include <sol.hpp>
#include <utility>

int main(int argc, char* argv[]) {
	sol::state lua;
	lua.script_file("config.lua");
	sf::RenderWindow window({ 
		lua["config"]["resolution"]["x"].get<unsigned>(),
		lua["config"]["resolution"]["y"].get<unsigned>()}, 
		"Bubble Warrior Adventures");
	window.setVerticalSyncEnabled(true);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		window.clear();
		window.display();
	}
	return 0;
}