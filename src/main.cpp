#include "window.hpp"
#include "input.hpp"

#include "sceneroot.hpp"

#include "component.hpp"
#include "components/transform.hpp"
#include "components/renderer.hpp"
#include "components/camera.hpp"
#include "components/custom.hpp"

#include "resource_manager.hpp"

#include <iostream>
#include <memory>

class MyComponent : public components::CustomComponent {
public:

	int spawnCount = 0;
	components::Transform* tcomp;

	MyComponent(Object* parent) : CustomComponent(parent)
	{
		tcomp = m_parent->getComponent<components::Transform>();
		tcomp->translate({ 0.0f, 0.0f, -10.0f });
		tcomp->scale({ 0.25f, 0.25f, 1.0f });
		tcomp->rotate(3.14159f / 2.0f, { 0.0f, 1.0f, 0.0f });
	}

	void onUpdate(glm::mat4 t) override {
		float& x = tcomp->m_transformMatrix[3][0];
		float& y = tcomp->m_transformMatrix[3][1];
		float& z = tcomp->m_transformMatrix[3][2];

		x = m_parent->window()->getMouseNormX() * 3.0f;
		y = (m_parent->window()->getMouseNormY() - 1.3f) * 3.0f;
	}

};

class CameraController : public components::CustomComponent {
public:

	components::Transform* tcomp;

	CameraController(Object* parent) : CustomComponent(parent)
	{
		tcomp = m_parent->getComponent<components::Transform>();
	}

	void onUpdate(glm::mat4 t) override {
		float& x = tcomp->m_transformMatrix[3][0];
		float& y = tcomp->m_transformMatrix[3][1];
		float& z = tcomp->m_transformMatrix[3][2];
		float dt = m_parent->window()->getLastFrameTime();
		float dx = m_parent->input()->getAxis("movex");
		float dz = m_parent->input()->getAxis("movey");

		glm::vec3 dxRotated = { dx * dt, 0.0f, 0.0f };

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

	mainScene.createChild("car")->createComponent<MyComponent>();
	mainScene.getChild("car")->createComponent<components::Renderer>();

	mainScene.createChild("cam")->createComponent<components::Camera>()->usePerspective(70.0f);

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

		mainScene.updateStuff();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();
	
	}	

	return 0;

}
