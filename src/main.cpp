#include "game.hpp"

#include "window.hpp"
#include <exception>

int main(int, char *[])
{
	try {
		playGame();
	}
	catch (const std::exception& e) {
		Window::errorBox(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
