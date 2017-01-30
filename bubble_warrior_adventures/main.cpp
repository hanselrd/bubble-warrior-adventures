#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
	sf::RenderWindow window({ 800, 600 }, "Bubble Warrior Adventures");
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