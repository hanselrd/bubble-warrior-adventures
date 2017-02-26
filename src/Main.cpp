#include <iostream>
#include <stdexcept>
#include "Game.hpp"

int main(int argc, char** argv) {
	try {
		Game g;
		g.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
