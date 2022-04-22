#include "window.hpp"
#include "input.hpp"

#include "glad/glad.h"

#include <iostream>
#include <memory>
#include <thread>

int main()
{

	std::shared_ptr<window::Window> win(new window::Window("sdltest"));

	// input class requires a reference to the window class
	std::unique_ptr<input::Input> input(new input::Input(win));

	// menu, settings controls
	input->addInputButton("fullscreen", input::KEYBOARD, SDL_SCANCODE_F11);
	input->addInputButton("quit", input::KEYBOARD, SDL_SCANCODE_ESCAPE);

	// game buttons
	input->addInputButton("fire", input::MOUSE, window::M_LEFT);
	input->addInputButton("aim", input::MOUSE, window::M_RIGHT);

	// game movement, looking
	input->addInputButtonAsAxis("movex", input::KEYBOARD, SDL_SCANCODE_D, SDL_SCANCODE_A);
	input->addInputButtonAsAxis("movey", input::KEYBOARD, SDL_SCANCODE_W, SDL_SCANCODE_S);

	input->addInputAxis("lookx", input::MOUSE, input::MOUSE_AXIS_X);
	input->addInputAxis("looky", input::MOUSE, input::MOUSE_AXIS_Y);

//	win->setVSync(true);
	win->setVSync(false);

	win->setRelativeMouseMode(false);

	// single-threaded game loop
	while (!win->shouldClose()) {

		// logic
		if (input->getButtonPress("fullscreen")) {
			win->toggleFullscreen();
		}
		if (input->getButtonPress("quit")) {
			win->setCloseFlag();
		}

		// draw
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// swap
		win->swapBuffers();

		// events
		win->getInputAndEvents();

		std::cout << "FPS: " << win->getFPS() << "\n";
	
	}

	return 0;

}
