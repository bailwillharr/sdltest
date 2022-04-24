#include "window.hpp"
#include "input.hpp"
#include "scene.hpp"

#include "component.hpp"
#include "components/transform.hpp"
#include "components/camera.hpp"

#include "glad/glad.h"

#include <iostream>
#include <memory>
#include <thread>

int main()
{

	std::shared_ptr<window::Window> win(new window::Window("sdltest"));

	// input class requires a reference to the window class
	std::unique_ptr<input::Input> input(new input::Input(win));

	std::unique_ptr<scene::Scene> mainScene(new scene::Scene());

	auto comp1 = mainScene->getRoot()->getComponent<component::Camera>();
	if (comp1 != nullptr) {
		std::cout << comp1->getID() << "\n";
		std::cout << comp1->getName() << "\n";
	}
	auto comp2 = mainScene->getRoot()->getComponent<component::Transform>();
	if (comp2 != nullptr) {
		std::cout << comp2->getID() << "\n";
		std::cout << comp2->getName() << "\n";
	}

	// menu, settings controls
	input->addInputButton("fullscreen", input::KEYBOARD, SDL_SCANCODE_F11);
	input->addInputButton("quit", input::KEYBOARD, SDL_SCANCODE_ESCAPE);
	// game buttons
	input->addInputButton("fire", input::MOUSE, window::M_LEFT);
	input->addInputButton("aim", input::MOUSE, window::M_RIGHT);
	// game movement
	input->addInputButtonAsAxis("movex", input::KEYBOARD, SDL_SCANCODE_D, SDL_SCANCODE_A);
	input->addInputButtonAsAxis("movey", input::KEYBOARD, SDL_SCANCODE_W, SDL_SCANCODE_S);
	// looking around
	input->addInputAxis("lookx", input::MOUSE, input::MOUSE_AXIS_X);
	input->addInputAxis("looky", input::MOUSE, input::MOUSE_AXIS_Y);

	win->setVSync(false);
	win->setRelativeMouseMode(false);

	// single-threaded game loop
	while (win->isRunning()) {

		// logic

		if (input->getButtonPress("fullscreen"))
			win->toggleFullscreen();

		if (input->getButtonPress("quit"))
			win->setCloseFlag();

		// draw
		glClearColor(0.69, 0.69, 0.420, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// swap
		win->swapBuffers();

		// events
		win->getInputAndEvents();

//		std::cout << "FPS: " << win->getFPS() << "\n";
//		std::cout << "FOCUS: " << win->hasFocus() << "\n";
	
	}

	return 0;

}
