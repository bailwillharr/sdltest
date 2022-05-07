#include "engine/window.hpp"
#include "engine/input.hpp"

#include "engine/ecs/sceneroot.hpp"

#include "engine/ecs/component.hpp"
#include "engine/ecs/components/transform.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	engine::Window win("sdltest");

	// input class requires a reference to the window class
	engine::Input input(win);

	// scene stuff
	engine::ecs::SceneRoot mainScene("My Scene");

	mainScene.createChild("car").lock()->createChild("engine").lock()->createChild("pistons");
	mainScene.getChildren().back().lock()->getChildren().back().lock()->createChild("camshaft");
	mainScene.getChildren().back().lock()->getChildren().back().lock()->createChild("crankshaft");
	mainScene.getChildren().back().lock()->createChild("wheels");
	mainScene.getChildren().back().lock()->createChild("doors");
	mainScene.getChildren().back().lock()->createChild("transmission");
	mainScene.getChildren().back().lock()->getChildren().back().lock()->createChild("flywheel");

	mainScene.printTree();

	// menu, settings controls
	input.addInputButton("fullscreen", engine::KEYBOARD, SDL_SCANCODE_F11);
	input.addInputButton("quit", engine::KEYBOARD, SDL_SCANCODE_ESCAPE);
	input.addInputButton("quit", engine::KEYBOARD, SDL_SCANCODE_Q);
	// game buttons
	input.addInputButton("fire", engine::MOUSE, engine::M_LEFT);
	input.addInputButton("aim", engine::MOUSE, engine::M_RIGHT);
	// game movement
	input.addInputButtonAsAxis("movex", engine::KEYBOARD, SDL_SCANCODE_D, SDL_SCANCODE_A);
	input.addInputButtonAsAxis("movey", engine::KEYBOARD, SDL_SCANCODE_W, SDL_SCANCODE_S);
	// looking around
	input.addInputAxis("lookx", engine::MOUSE, engine::MOUSE_AXIS_X);
	input.addInputAxis("looky", engine::MOUSE, engine::MOUSE_AXIS_Y);

	input.addInputButton("jump", engine::KEYBOARD, SDL_SCANCODE_SPACE);

	win.setVSync(true);
	win.setRelativeMouseMode(true);

	uint64_t lastSecond = win.getNanos();

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getNanos() >= lastSecond + engine::BILLION) {
			std::cout << "FPS: " << win.getFPS() << "\n";
			lastSecond = win.getNanos();
		}

		// logic

		if (input.getButtonPress("fullscreen"))
			win.toggleFullscreen();
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if (input.getButtonPress("jump")) {
			mainScene.createComponent<engine::ecs::components::Transform>();
		}

		// draw

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();
	
	}

	return 0;

}
