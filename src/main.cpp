#include "engine/window.hpp"
#include "engine/input.hpp"

#include "engine/ecs/sceneroot.hpp"

#include "engine/ecs/component.hpp"
#include "engine/ecs/components/transform.hpp"
#include "engine/ecs/components/renderer.hpp"
#include "engine/ecs/components/camera.hpp"

#include "engine/debug/timer.hpp"

#include <iostream>
#include <memory>
#include <thread>

class MyComponent : public engine::ecs::Component {
public:
	MyComponent(engine::ecs::Object* parent) : Component(parent, "MyComponent") {}
	void onUpdate(glm::mat4 transform) override
	{
		glm::mat4& t = m_parent->getComponent<engine::ecs::components::Transform>()->m_transformMatrix;
		t = glm::rotate(t, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	void onRender(glm::mat4 transform) override
	{
		(void)transform;
	}
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
	mainScene.getChild("car")->createComponent<engine::ecs::components::Renderer>();

	mainScene.getChild("car")->createChild("door")->createComponent<engine::ecs::components::Renderer>();
	mainScene.getChild("car")->getChild("door")->createComponent<MyComponent>();

	glm::mat4& t = mainScene.getChild("car")->getComponent<engine::ecs::components::Transform>()->m_transformMatrix;
	glm::mat4& t2 = mainScene.getChild("car")->getChild("door")->getComponent<engine::ecs::components::Transform>()->m_transformMatrix;

	t = glm::scale(t, glm::vec3{0.5f, 0.5f, 1.0f});
	t2 = glm::translate(t2, glm::vec3{-1.0f, 0.0f, 0.0f});
	t2 = glm::scale(t2, glm::vec3{ 0.25f, 0.25f, 1.0f });

	mainScene.createChild("cam")->createComponent<engine::ecs::components::Camera>();
		
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
			win.setTitle(std::to_string(win.getFPS()) + " fps, avg: " + std::to_string(win.getAvgFPS()) + " fps");
		}
		
		// logic
		mainScene.updateScene();

		if (input.getButtonPress("fullscreen")) {
			win.toggleFullscreen();
			if (win.isFullscreen())
				win.setRelativeMouseMode(true);
			else
				win.setRelativeMouseMode(false);
		}
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if(input.getButtonPress("jump"))
			win.setVSync(!win.getVSync());

		if(input.getButtonPress("fire"))
			mainScene.deleteChild("car");
	
		// draw
		glClear(GL_COLOR_BUFFER_BIT);
		mainScene.renderScene();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();
	
	}

	return 0;

}
