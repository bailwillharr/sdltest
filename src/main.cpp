#include "window.hpp"
#include "input.hpp"

#include "scene.hpp"
//#include "object.hpp"

//#include "component.hpp"
//#include "components/transform.hpp"
//#include "components/camera.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	std::unique_ptr<window::Window> win = std::make_unique<window::Window>("sdltest");

	// input class requires a reference to the window class
	std::unique_ptr<input::Input> input = std::make_unique<input::Input>(*win);

	// scene stuff
	std::unique_ptr<scene::Scene> mainScene(new scene::Scene("cubes"));

	/*
	mainScene->getRoot()->getCompList()->createComponent<component::Camera>(std::make_shared<component::Camera>(mainScene->getRoot()->getCompList()));

	auto comp1 = mainScene->getRoot()->getCompList()->getComponent<component::Camera>();
	if (comp1 != nullptr) {
		std::cout << comp1->getID() << "\n";
		std::cout << comp1->getTypeName() << "\n";
	}
	auto comp2 = mainScene->getRoot()->getCompList()->getComponent<component::Transform>();
	if (comp2 != nullptr) {
		std::cout << comp2->getID() << "\n";
		std::cout << comp2->getTypeName() << "\n";
	}

	mainScene->getRoot()->createChild("car")->createChild("engine")->createChild("pistons");
	mainScene->getRoot()->getChildren().back()->getChildren().back()->createChild("camshaft");
	mainScene->getRoot()->getChildren().back()->getChildren().back()->createChild("crankshaft");
	mainScene->getRoot()->getChildren().back()->createChild("wheels");
	mainScene->getRoot()->getChildren().back()->createChild("doors");
	mainScene->getRoot()->getChildren().back()->createChild("transmission");
	mainScene->getRoot()->getChildren().back()->getChildren().back()->createChild("flywheel");

	std::cout << "TREE:\n";
	mainScene->getRoot()->printTree();

	*/



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



	win->setVSync(true);
	win->setRelativeMouseMode(true);

	uint64_t lastSecond = win->getNanos();

	// single-threaded game loop
	while (win->isRunning()) {

		if (win->getNanos() >= lastSecond + window::BILLION) {
			std::cout << "FPS: " << win->getFPS() << "\n";
			lastSecond = win->getNanos();
		}

		// logic

		if (input->getButtonPress("fullscreen"))
			win->toggleFullscreen();
		if (input->getButtonPress("quit"))
			win->setCloseFlag();

		// draw

		// swap
		win->swapBuffers();

		// events
		win->getInputAndEvents();
	
	}

	return 0;

}
