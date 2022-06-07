#include "game.hpp"

#include "window.hpp"
#include "input.hpp"

#include "sceneroot.hpp"

#include "component.hpp"
#include "components/transform.hpp"
#include "components/renderer.hpp"
#include "components/camera.hpp"
#include "components/custom.hpp"

#include "resource_manager.hpp"

class MyComponent : public components::CustomComponent {
public:

	components::Transform* tcomp;
	components::Renderer* rcomp;

	MyComponent(Object* parent) : CustomComponent(parent)
	{
		tcomp = this->parent.getComponent<components::Transform>();
		rcomp = this->parent.getComponent<components::Renderer>();

		tcomp->translate({ 0.0f, 0.0f, -10.0f });
		tcomp->rotate(3.14159f / 2.0f, { 0.0f, 1.0f, 0.0f });
	}

	void onUpdate(glm::mat4 t) override
	{
		float dt = (float)parent.win.dt() / (float)BILLION;
		tcomp->rotate(dt * 2.0f, { 0.0f, 1.0f, 0.0f });
	}

};

class CameraController : public components::CustomComponent {
public:

	components::Transform* tcomp;

	CameraController(Object* parent) :
		CustomComponent(parent)
	{
		tcomp = this->parent.getComponent<components::Transform>();
	}

	void onUpdate(glm::mat4 t) override {
		const float& x = tcomp->m_transformMatrix[3][0];
		const float& y = tcomp->m_transformMatrix[3][1];
		const float& z = tcomp->m_transformMatrix[3][2];
		float dt = (float)win.dt() / (float)BILLION;
		float dx = inp.getAxis("movex");
		float dy = (inp.getButton("jump") ? 10.0f : 0.0f) - (inp.getButton("sneak") ? 10.0f : 0.0f);
		float dz = inp.getAxis("movey");

		float speed = 3.0f;

		tcomp->translate({ dx * dt * speed, dy * speed * dt, -dz * dt * speed });

		float rotDX = inp.getAxis("looky") * -0.005f;
		float rotDY = inp.getAxis("lookx") * -0.005f;

		tcomp->rotate(rotDY, glm::vec3{ 0.0f, 1.0f, 0.0f });

	}

};

void playGame()
{

	Window win("sdltest");
	Input input(win);
	ResourceManager resMan;
	SceneRoot mainScene("My Scene", { &win, &input, &resMan });

	mainScene.createChild("gun")->createComponent<components::Renderer>();
	mainScene.getChild("gun")->createComponent<MyComponent>();

	const auto rcomp = mainScene.getChild("gun")->getComponent<components::Renderer>();

	mainScene.createChild("donut")->createComponent<components::Renderer>()->setMesh("donut.mesh");
	//mainScene.getChild("donut")->createComponent<MyComponent>();

	mainScene.createChild("cam")->createComponent<components::Camera>()->usePerspective(70.0f);
	mainScene.getChild("cam")->createComponent<CameraController>();

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

		if (win.getLastFrameStamp() >= lastTick + (BILLION / 20)) {
			lastTick = win.getLastFrameStamp();
			win.setTitle(std::to_string(win.getFPS()) + " fps, avg: " + std::to_string(win.getAvgFPS()) + " fps");
		}

		// logic

		if (input.getButtonPress("fullscreen"))
			win.toggleFullscreen();
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if (win.getKeyPress(inputs::Key::TAB)) {
			//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "RESOURCES", resMan.getResourcesListString()->c_str(), win.m_handle);
		}

		mainScene.updateStuff();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();

	}

}