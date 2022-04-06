#include "window.hpp"
#include "input.hpp"

#include "glad/glad.h"

#include <iostream>
#include <memory>
#include <thread>

int main()
{

	std::shared_ptr<window::Window> win(new window::Window("sdltest"));
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

	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;

	win->setVSync(true);

	win->setRelativeMouseMode(true);

	// single-threaded game loop
	while (!win->shouldClose()) {

		// logic
		if (input->getButtonDown("fullscreen")) {
			win->toggleFullscreen();
		}
		if (input->getButtonDown("quit")) {
			win->setCloseFlag();
		}

		red += input->getAxis("movey") / 1000.0f;
		if (red > 1.0f) red = 1.0f;
		if (red < 0.0f) red = 0.0f;
		green += input->getAxis("movex") / 1000.0f;
		if (green > 1.0f) green = 1.0f;
		if (green < 0.0f) green = 0.0f;
		blue += input->getAxis("looky") / 1000.0f;
		if (blue > 1.0f) blue = 1.0f;
		if (blue < 0.0f) blue = 0.0f;

		// draw
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// swap
		win->swapBuffers();

		// events
		win->getInputAndEvents();

	}

	Uint64 ticksum = 0;
	Uint64 perfsum = 0;
	for (int j = 0; j < 10; j++) {
		Uint64 start = SDL_GetPerformanceCounter();
		for (int i = 0; i < 10000000; i++) {
			SDL_GetTicks();
		}
		Uint64 end = SDL_GetPerformanceCounter();
		std::cout << "getTicks " << end - start << std::endl;
		ticksum += end - start;
		Uint64 start2 = SDL_GetPerformanceCounter();
		for (int i = 0; i < 10000000; i++) {
			SDL_GetPerformanceCounter();
		}
		Uint64 end2 = SDL_GetPerformanceCounter();
		std::cout << "getPerfC " << end2 - start2 << std::endl;
		perfsum += end2-start2;
	}
	std::cout << "getTicks mean " << ticksum / 10 << std::endl;
	std::cout << "getPerfC mean " << perfsum / 10 << std::endl;
	return 0;

}
