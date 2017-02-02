#include "game.hpp"

int main(int argc, char** argv) {
	try
	{
		bwa::Game g;
		g.run();
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << "Press enter to exit." << std::endl;
		std::cin.get();
	}
	return 0;
}