#include "window.hpp"
#include "input.hpp"

#include "sceneroot.hpp"

#include "component.hpp"
#include "components/transform.hpp"
#include "components/renderer.hpp"
#include "components/camera.hpp"

#include "resource_manager.hpp"

#include "debug/timer.hpp"

#include <iostream>
#include <memory>
#include <thread>

class MyComponent : public Component {
public:
	MyComponent(Object* parent) : Component(parent, "MyComponent") {}
	void onUpdate(glm::mat4 transform) override
	{
		glm::mat4& t = m_parent->getComponent<components::Transform>()->m_transformMatrix;
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

	Window win("sdltest");
	Input input(win);
	ResourceManager resMan;
	SceneRoot mainScene("My Scene");

	{
		auto mat1 = resMan.get<resources::Shader>("basic.glsl");
		auto mat2 = resMan.get<resources::Shader>("basic.glsl");
	}
	auto mat3 = resMan.get<resources::Shader>("basic.glsl");
	auto mat4 = resMan.get<resources::Shader>("basic.glsl");

	/*
	mainScene.createChild("car");
	mainScene.getChild("car")->createComponent<ecs::components::Renderer>();

	mainScene.getChild("car")->createChild("door")->createComponent<ecs::components::Renderer>();
	mainScene.getChild("car")->getChild("door")->createComponent<MyComponent>();

	glm::mat4& t = mainScene.getChild("car")->getComponent<ecs::components::Transform>()->m_transformMatrix;
	glm::mat4& t2 = mainScene.getChild("car")->getChild("door")->getComponent<ecs::components::Transform>()->m_transformMatrix;

	t = glm::scale(t, glm::vec3{0.5f, 0.5f, 1.0f});
	t2 = glm::translate(t2, glm::vec3{-1.0f, 0.0f, 0.0f});
	t2 = glm::scale(t2, glm::vec3{ 0.25f, 0.25f, 1.0f });

	mainScene.createChild("cam")->createComponent<ecs::components::Camera>();

	*/
		
//	mainScene.printTree();

	// menu, settings controls
	input.addInputButton("fullscreen", inputs::Key::F11);
	input.addInputButton("quit", inputs::Key::ESCAPE);
	input.addInputButton("quit", inputs::Key::Q);
	// game buttons
	input.addInputButton("fire", inputs::MouseButton::M_LEFT);
	input.addInputButton("aim", inputs::MouseButton::M_RIGHT);
	// game movement
	input.addInputButtonAsAxis("movex", inputs::Key::D, inputs::Key::A);
	input.addInputButtonAsAxis("movey", inputs::Key::W, inputs::Key::S);
	// looking around
	input.addInputAxis("lookx", inputs::MouseAxis::X);
	input.addInputAxis("looky", inputs::MouseAxis::Y);

	input.addInputButton("jump", inputs::Key::SPACE);

	win.setVSync(true);
	win.setRelativeMouseMode(false);

	uint64_t lastTick = win.getNanos();

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getNanos() >= lastTick + (BILLION/20)) {
			lastTick = win.getNanos();
			win.setTitle(std::to_string(win.getFPS()) + " fps, avg: " + std::to_string(win.getAvgFPS()) + " fps");
		}
		
		// logic

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

		mainScene.updateScene();
	
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
