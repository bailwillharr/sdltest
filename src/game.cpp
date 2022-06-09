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

class CameraController : public components::CustomComponent {
public:

	float m_yaw = 0.0f;
	float m_pitch = 0.0f;

	components::Transform* tcomp;

	CameraController(Object* parent) :
		CustomComponent(parent)
	{
		tcomp = this->parent.getComponent<components::Transform>();

		tcomp->position.x -= 2.0f;
	}

	void onUpdate(glm::mat4 t) override {

		// calculate new position

		const float dt = win.dt();
		constexpr float SPEED = 3.0f;

		const float dx = inp.getAxis("movex") * dt * SPEED;
		const float dy = ((inp.getButton("jump") ? 10.0f : 0.0f) - (inp.getButton("sneak") ? 10.0f : 0.0f)) * dt * SPEED;
		const float dz = (-inp.getAxis("movey")) * dt * SPEED;

		// calculate new pitch and yaw

		constexpr float MAX_PITCH = glm::pi<float>() / 2.0f;
		constexpr float MIN_PITCH = -glm::pi<float>() / 2.0f;

		float dPitch = inp.getAxis("looky") * -0.005f;
		m_pitch += dPitch;
		if (m_pitch <= MIN_PITCH || m_pitch >= MAX_PITCH) {
			m_pitch -= dPitch;
		}
		m_yaw += inp.getAxis("lookx") * -0.005f;

		// update position relative to camera direction in xz plane
		const glm::vec3 dxRotated = glm::rotateY(glm::vec3{dx, 0.0f, 0.0f}, m_yaw);
		const glm::vec3 dzRotated = glm::rotateY(glm::vec3{0.0f, 0.0f, dz}, m_yaw);
		tcomp->position += dzRotated;
		tcomp->position += dxRotated;
		tcomp->position.y += dy;

		// pitch quaternion
		const float halfPitch = m_pitch/2.0f;
		glm::quat pitchQuat;
		pitchQuat.x = glm::sin(halfPitch);
		pitchQuat.y = 0.0f;
		pitchQuat.z = 0.0f;
		pitchQuat.w = glm::cos(halfPitch);

		// yaw quaternion
		const float halfYaw = m_yaw/2.0f;
		glm::quat yawQuat;
		yawQuat.x = 0.0f;
		yawQuat.y = glm::sin(halfYaw);
		yawQuat.z = 0.0f;
		yawQuat.w = glm::cos(halfYaw);

		// update rotation
		tcomp->rotation = yawQuat * pitchQuat;

	}

};

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

		const float speed = 1.0f;

		if (win.getKey(inputs::Key::LEFT))
			x -= dt * speed;
		if (win.getKey(inputs::Key::RIGHT))
			x += dt * speed;
		if (win.getKey(inputs::Key::UP))
			z -= dt * speed;
		if (win.getKey(inputs::Key::DOWN))
			z += dt * speed;
	}

};

void playGame()
{

	Window win("sdltest");
	Input input(win); /* Input Manager */
	ResourceManager resMan;
	SceneRoot mainScene({ &win, &input, &resMan });
	
	mainScene.createChild("donut")->createComponent<components::Renderer>()->setMesh("donut.mesh");

	mainScene.createChild("cam")->createComponent<components::Camera>()->usePerspective(70.0f);
	mainScene.getChild("cam")->createComponent<CameraController>();
	mainScene.getChild("cam")->createChild("gun")->createComponent<components::Renderer>()->setMesh("gun.mesh");
	mainScene.getChild("cam")->getChild("gun")->createComponent<ArrowsMovement>();
	mainScene.getChild("cam")->getChild("gun")->getComponent<components::Transform>()
		->position = glm::vec3{3.0f, -10.0f, -10.0f};
	mainScene.getChild("cam")->getChild("gun")->getComponent<components::Transform>()
		->rotation = glm::angleAxis(glm::pi<float>(), glm::vec3{0.0f, 1.0f, 0.0f});

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

		if (input.getButtonPress("fullscreen")) {
			if (win.isFullscreen()) {
				win.setFullscreen(false);
			} else {
				win.setFullscreen(true, false); // disable exclusive mode, use borderless window
			}
		}
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
