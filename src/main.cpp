#include "window.hpp"

#include "glad/glad.h"

#include <iostream>
#include <memory>
#include <thread>

int main()
{

	std::unique_ptr<window::Window> win(new window::Window("sdltest"));

	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;

	win->setVSync(true);

	win->setRelativeMouseMode(true);

	// single-threaded game loop
	while (!win->shouldClose()) {

		// logic
		if (win->getKeyPress(SDL_SCANCODE_F11)) {
			win->toggleFullscreen();
		}
		if (win->getButtonPress(window::MouseButton::LEFT)) {
			red += 0.5f;
			if (red > 1.0f) red = 0.0f;
		}
		if (win->getButtonPress(window::MouseButton::MIDDLE)) {
			green += 0.5f;
			if (green > 1.0f) green = 0.0f;
		}
		if (win->getButtonPress(window::MouseButton::RIGHT)) {
			blue += 0.5f;
			if (blue > 1.0f) blue = 0.0f;
		}

		red += win->getMouseScrollY() * 0.01f;
		
		// draw
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// swap
		win->swapBuffers();

		// events
		win->getInputAndEvents();

	}

	return 0;

}
