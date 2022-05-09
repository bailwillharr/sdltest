#include "engine/window.hpp"
#include "engine/input.hpp"

#include "engine/ecs/sceneroot.hpp"

#include "engine/ecs/component.hpp"
#include "engine/ecs/components/transform.hpp"

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
	input.addInputButton("fullscreen", engine::inputs::Key::F11);
	input.addInputButton("quit", engine::inputs::Key::ESCAPE);
	input.addInputButton("quit", engine::inputs::Key::Q);
	// game buttons
	input.addInputButton("fire", engine::inputs::MouseButton::M_LEFT);
	input.addInputButton("aim", engine::inputs::MouseButton::M_RIGHT);
	// game movement
	input.addInputButtonAsAxis("movex", engine::inputs::Key::D, engine::inputs::Key::A);
	input.addInputButtonAsAxis("movey", engine::inputs::Key::W, engine::inputs::Key::S);
	// looking around
	input.addInputAxis("lookx", engine::inputs::MouseAxis::X);
	input.addInputAxis("looky", engine::inputs::MouseAxis::Y);

	input.addInputButton("jump", engine::inputs::Key::SPACE);

	win.setVSync(false);
	win.setRelativeMouseMode(false);

	uint64_t lastTick = win.getNanos();

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getNanos() >= lastTick + (engine::BILLION/20)) {
			lastTick = win.getNanos();
			win.setTitle(std::to_string(win.getFPS()) + " fps");
		}

		// logic

		if (input.getButtonPress("fullscreen"))
			win.toggleFullscreen();
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if (input.getButtonPress("jump")) {
			std::cerr << mainScene.getChild("car").lock()->getComponent<engine::ecs::components::Transform>().lock()->getID() << "\n";
		}

		// draw

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();
	
	}

	return 0;

}
