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

#include <glm/gtx/rotate_vector.hpp>

class MyComponent : public components::CustomComponent {
public:

	components::Transform* tcomp;
	components::Renderer* rcomp;

	const float SPEED = 3.0f;
	float sf = 1.0f;
	float sfrate = SPEED;

	MyComponent(Object* parent) : CustomComponent(parent)
	{
		tcomp = this->parent.getComponent<components::Transform>();
		rcomp = this->parent.getComponent<components::Renderer>();

		tcomp->position.z = -10.0f;

		tcomp->rotation = glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3{0.0f, 1.0f, 0.0f});
	}

	void onUpdate(glm::mat4 t) override
	{
		const float dt = win.dt();
		//tcomp->rotation.y += dt * 2.0f;

		if (sf >= 10.0f) {
			sfrate = -SPEED;
		} else if (sf <= 1.0f) {
			sfrate = SPEED;
		}
		sf += sfrate * dt;
		tcomp->scale.x = sf;
	}

};

class CameraController : public components::CustomComponent {
public:

	components::Transform* tcomp;

	CameraController(Object* parent) :
		CustomComponent(parent)
	{
		tcomp = this->parent.getComponent<components::Transform>();

		tcomp->position.x -= 2.0f;
	}

	void onUpdate(glm::mat4 t) override {
		const float dt = win.dt();
		const float dx = inp.getAxis("movex");
		const float dy = (inp.getButton("jump") ? 10.0f : 0.0f) - (inp.getButton("sneak") ? 10.0f : 0.0f);
		const float dz = -inp.getAxis("movey");

		float speed = 3.0f;

		tcomp->position.x += dx * dt * speed;
		tcomp->position.y += dy * dt * speed;
		tcomp->position.z += dz * dt * speed;

		float rotDX = inp.getAxis("looky") * -0.005f;
		float rotDY = inp.getAxis("lookx") * -0.005f;

		glm::vec3 lookDir{0.0f, 0.0f, -1.0f};
		lookDir = glm::rotateY(lookDir, rotDY);

		tcomp->rotation = glm::quatLookAt(lookDir, glm::vec3{0.0f, 1.0f, 0.0f});

	}

};

void playGame()
{

	Window win("sdltest");
	Input input(win); /* Input Manager */
	ResourceManager resMan;
	SceneRoot mainScene({ &win, &input, &resMan });
	
	mainScene.createChild("gun")->createComponent<components::Renderer>();
	mainScene.getChild("gun")->createComponent<MyComponent>();

	mainScene.createChild("donut")->createComponent<components::Renderer>()->setMesh("donut.mesh");

	mainScene.createChild("cam")->createComponent<components::Camera>()->usePerspective(70.0f);
	mainScene.getChild("cam")->createComponent<CameraController>();

	class ArrowsMovement : public components::CustomComponent {
	public:
		components::Transform* tcomp;

		ArrowsMovement(Object* parent) :
			CustomComponent(parent)
		{
			tcomp = this->parent.getComponent<components::Transform>();
		}

		void onUpdate(glm::mat4) override
		{
			float& x = tcomp->position.x;
			float& y = tcomp->position.y;
			float& z = tcomp->position.z;
			const float dt = win.dt();

			const float speed = 100.0f;

			if (win.getKey(inputs::Key::LEFT))
				x += dt * speed;
			if (win.getKey(inputs::Key::RIGHT))
				x -= dt * speed;
			if (win.getKey(inputs::Key::UP))
				z += dt * speed;
			if (win.getKey(inputs::Key::DOWN))
				z -= dt * speed;
		}
	
	};

	mainScene.createChild("gunMaster")->createComponent<ArrowsMovement>();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			const std::string name = "gun" + std::to_string(i) + "_" + std::to_string(j);
			mainScene.getChild("gunMaster")->createChild(name)->getComponent<components::Transform>()->position = { (float)i * 2.5f, 0.0f, (float)j * 16.0f };
			mainScene.getChild("gunMaster")->getChild(name)->createComponent<components::Renderer>();
		}
	}

#ifdef SDLTEST_DEBUG
	mainScene.printTree();
#endif

	// menu, settings controls
	input.addInputButton("fullscreen", inputs::Key::F11);
	input.addInputButton("togglefocus", inputs::Key::Q);
	input.addInputButton("quit", inputs::Key::ESCAPE);
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
			win.setTitle(std::to_string(win.getFPS()) + " fps, avg: " + std::to_string(win.getAvgFPS()) + " fps, frames: " + std::to_string(win.getFrameCount()));
		}

		// logic

		if (input.getButtonPress("fullscreen"))
			win.toggleFullscreen();
		if (input.getButtonPress("togglefocus")) {
			bool captured = win.mouseCaptured();
			win.setRelativeMouseMode(!captured);
			input.setDeviceActive(InputDevice::MOUSE, !captured);
		}
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if (win.getKeyPress(inputs::Key::TAB)) {
			win.infoBox("RESOURCES", resMan.getResourcesListString()->c_str());
		}

		mainScene.updateStuff();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();

	}

}
