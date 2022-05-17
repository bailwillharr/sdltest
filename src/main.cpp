#include "engine/window.hpp"
#include "engine/input.hpp"

#include "engine/ecs/sceneroot.hpp"

#include "engine/ecs/component.hpp"
#include "engine/ecs/components/transform.hpp"
#include "engine/ecs/components/renderer.hpp"

#include <iostream>
#include <memory>
#include <thread>

class MyComponent : public engine::ecs::Component {
public:
	MyComponent(engine::ecs::Object* parent) : Component(parent, "MyComponent") {}
	void onUpdate(glm::mat4 transform) override
	{
		(void)transform;
	}
	void onRender(glm::mat4 transform) override
	{
		(void)transform;
		std::cout << "TRANSFORM: " << transform[0][0] << "\n";
	}
	void doThings() { std::cout << "YEE YEE\n"; }
};

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	engine::Window win("sdltest");

	// input class requires a reference to the window class
	engine::Input input(win);

	// scene stuff
	engine::ecs::SceneRoot mainScene("My Scene");

	mainScene.createChild("car");
	mainScene.getChild("car").lock()->createComponent<MyComponent>();
	mainScene.getChild("car").lock()->createComponent<engine::ecs::components::Renderer>();

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

	win.setVSync(true);
	win.setRelativeMouseMode(false);

	uint64_t lastTick = win.getNanos();

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getNanos() >= lastTick + (engine::BILLION/20)) {
			lastTick = win.getNanos();
			win.setTitle(std::to_string(win.getFPS()) + " fps");
		}

		// logic
		mainScene.updateScene();

		if (input.getButtonPress("fullscreen"))
			win.toggleFullscreen();
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if (input.getButtonPress("jump")) {
			std::cerr << mainScene.getChild("car").lock()->getComponent<engine::ecs::components::Transform>().lock()->getID() << "\n";
		}

		// draw
		mainScene.renderScene();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();
	
	}

	return 0;

}
