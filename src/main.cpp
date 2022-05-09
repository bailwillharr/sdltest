#include "engine/window.hpp"
#include "engine/input.hpp"

#include "engine/ecs/sceneroot.hpp"

#include "engine/ecs/component.hpp"
#include "engine/ecs/components/transform.hpp"

#include "../engine/vendor/glad/include/glad/glad.h"

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
	input.addInputButton("fullscreen", engine::InputDevice::KEYBOARD, SDL_SCANCODE_F11);
	input.addInputButton("quit", engine::InputDevice::KEYBOARD, SDL_SCANCODE_ESCAPE);
	input.addInputButton("quit", engine::InputDevice::KEYBOARD, SDL_SCANCODE_Q);
	// game buttons
	input.addInputButton("fire", engine::InputDevice::MOUSE, static_cast<int>(engine::MouseButton::M_LEFT));
	input.addInputButton("aim", engine::InputDevice::MOUSE, static_cast<int>(engine::MouseButton::M_RIGHT));
	// game movement
	input.addInputButtonAsAxis("movex", engine::InputDevice::KEYBOARD, SDL_SCANCODE_D, SDL_SCANCODE_A);
	input.addInputButtonAsAxis("movey", engine::InputDevice::KEYBOARD, SDL_SCANCODE_W, SDL_SCANCODE_S);
	// looking around
	input.addInputAxis("lookx", engine::InputDevice::MOUSE, static_cast<int>(engine::MouseAxis::X));
	input.addInputAxis("looky", engine::InputDevice::MOUSE, static_cast<int>(engine::MouseAxis::Y));

	input.addInputButton("jump", engine::InputDevice::KEYBOARD, SDL_SCANCODE_SPACE);

	win.setVSync(true);
	win.setRelativeMouseMode(true);

	uint64_t lastSecond = win.getNanos();

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getNanos() >= lastSecond + engine::BILLION) {
			lastSecond = win.getNanos();
		}
		std::cerr << "FPS: " << win.getFPS() << " frame time: " << win.getLastFrameTime() << "\n";

		// logic

		if (input.getButtonPress("fullscreen"))
			win.toggleFullscreen();
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if (input.getButtonPress("jump")) {
			std::cerr << mainScene.getChild("car").lock()->getComponent<engine::ecs::components::Transform>().lock()->getID() << "\n";
		}

		// draw
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();
	
	}

	return 0;

}
