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

	int spawnCount = 0;

	MyComponent(Object* parent) : Component(parent, "MyComponent")
	{
		auto t = m_parent->getComponent<components::Transform>();
		t->translate({ -0.5f, -0.5f, 0.0f });
		t->scale({ 0.25f, 0.25f, 1.0f });
	}
	void onUpdate(glm::mat4 transform) override
	{

		using namespace components;

		if (m_parent->input()->getButtonPress("sneak")) {
			auto str = m_parent->resMan()->getResourcesListString();
			std::cout << *str;
		}

		if (m_parent->input()->getButtonPress("fire")) {
			if (spawnCount > 0) {
				spawnCount--;
				m_parent->getParent()->deleteChild("new" + std::to_string(spawnCount));
			}
		} else if (m_parent->input()->getButtonPress("aim")) {
			m_parent->getParent()->createChild("new" + std::to_string(spawnCount))->createComponent<Renderer>();
			m_parent->getParent()->getChild("new" + std::to_string(spawnCount))->getComponent<Transform>()->translate({ (float)m_parent->window()->getMouseX() / 320.0f - 1.0f, (480.0f - (float)m_parent->window()->getMouseY()) / 240.0f - 1.0f, 0.0f });
			m_parent->getParent()->getChild("new" + std::to_string(spawnCount))->getComponent<Transform>()->scale({ 0.25f, 0.25f, 1.0f });
			spawnCount++;
		}
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
	SceneRoot mainScene("My Scene", { &win, &input, &resMan });

	mainScene.createChild("car");
	mainScene.getChild("car")->createComponent<components::Renderer>();
	mainScene.getChild("car")->createComponent<MyComponent>();

	mainScene.printTree();

	// menu, settings controls
	input.addInputButton("fullscreen", inputs::Key::F11);
	input.addInputButton("quit", inputs::Key::ESCAPE);
	input.addInputButton("quit", inputs::Key::Q);
	// game buttons
	input.addInputButton("fire", inputs::MouseButton::M_LEFT);
	input.addInputButton("aim", inputs::MouseButton::M_RIGHT);
	input.addInputButton("jump", inputs::Key::SPACE);
	input.addInputButton("sneak", inputs::Key::LSHIFT);
	// game movement
	input.addInputButtonAsAxis("movex", inputs::Key::D, inputs::Key::A);
	input.addInputButtonAsAxis("movey", inputs::Key::W, inputs::Key::S);
	// looking around
	input.addInputAxis("lookx", inputs::MouseAxis::X);
	input.addInputAxis("looky", inputs::MouseAxis::Y);

	win.setVSync(false);
	win.setRelativeMouseMode(false);

	uint64_t lastTick = win.getNanos();

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getLastFrameStamp() >= lastTick + (BILLION/20)) {
			lastTick = win.getLastFrameStamp();
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
#ifndef SDLTEST_NOGFX
		glClear(GL_COLOR_BUFFER_BIT);
#endif
		mainScene.renderScene();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();
	
	}	

	return 0;

}
