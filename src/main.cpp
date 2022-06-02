#include "window.hpp"
#include "input.hpp"

#include "sceneroot.hpp"

#include "component.hpp"
#include "components/transform.hpp"
#include "components/renderer.hpp"
#include "components/camera.hpp"

#include "resource_manager.hpp"

#include <iostream>
#include <memory>

class MyComponent : public Component {
public:

	int spawnCount = 0;
	components::Transform* t;

	MyComponent(Object* parent) : Component(parent, "MyComponent")
	{
		t = m_parent->getComponent<components::Transform>();
		t->translate({ -0.5f, -0.5f, 0.0f });
		t->scale({ 0.25f, 0.25f, 1.0f });
	}
	void onUpdate(glm::mat4 transform) override
	{

		float& x = t->m_transformMatrix[3][0];
		float& y = t->m_transformMatrix[3][1];
		float& z = t->m_transformMatrix[3][2];

		x = m_parent->window()->getMouseNormX();
		y = m_parent->window()->getMouseNormY() - 1.3f;

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

#ifdef SDLTEST_DEBUG
	mainScene.printTree();
#endif

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
	win.setRelativeMouseMode(true);

	uint64_t lastTick = win.getNanos();

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getLastFrameStamp() >= lastTick + (BILLION/20)) {
			lastTick = win.getLastFrameStamp();
			win.setTitle(std::to_string(win.getFPS()) + " fps, avg: " + std::to_string(win.getAvgFPS()) + " fps");
		}
		
		// logic

		if (input.getButtonPress("fullscreen"))
			win.toggleFullscreen();
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if(input.getButtonPress("jump"))
			win.setVSync(!win.getVSync());
		if (input.getButtonPress("sneak"))
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "RESOURCES", resMan.getResourcesListString()->c_str(), win.m_handle);

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
