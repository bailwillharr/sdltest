#include "game.hpp"

#include "config.h"

#include "camera_controller.hpp"

#include "window.hpp"
#include "input.hpp"
#include "resource_manager.hpp"
#include "sceneroot.hpp"

#include "components/ui.hpp"
#include "components/renderer.hpp"
#include "components/transform.hpp"
#include "components/camera.hpp"

static void addObjects(SceneRoot& mainScene);
static void addInputs(Input& input);
static void gameLoop(Window& win, Input& input, ResourceManager& resMan, SceneRoot& mainScene);

void playGame()
{

	Window win("sdltest");
	Input input(win); /* Input Manager */
	ResourceManager resMan;
	SceneRoot mainScene({ &win, &input, &resMan });

	addObjects(mainScene);
	addInputs(input);

	gameLoop(win, input, resMan, mainScene);
	
}

static void addObjects(SceneRoot& mainScene)
{

	using namespace components;

	auto hud = mainScene.createChild("hud")->createComponent<UI>();

	auto floor = mainScene.createChild("floor");
	auto floorTransform = floor->getComponent<Transform>();
	floorTransform->scale = glm::vec3{16.0f, 16.0f, 16.0f};
	floorTransform->position = glm::vec3{ 0.0f, 0.0f, 0.0f };
	auto floorRenderer = floor->createComponent<Renderer>();
	floorRenderer->setMesh("floor.mesh");
	floor->getComponent<Renderer>()->setTexture("floor.glraw");

	auto cam = mainScene.createChild("cam");
	cam->getComponent<Transform>()->position = { 0.0f, 6.25f, 0.0f };
	cam->createComponent<Camera>()->usePerspective(70.0f);
	cam->createComponent<CameraController>();

	auto gun = cam->createChild("gun");
	auto gunTransform = gun->getComponent<Transform>();
	gunTransform->position = glm::vec3{ 0.375f, -1.25f, -1.25f };
	gunTransform->rotation = glm::angleAxis(glm::pi<float>(), glm::vec3{ 0.0f, 1.0f, 0.0f });
	gunTransform->scale = glm::vec3{ 0.125f, 0.125f, 0.125f };
	gun->createComponent<Renderer>()->setMesh("gun.mesh");

	auto cube = mainScene.createChild("cube");
	cube->createComponent<Renderer>()->setMesh("cube.mesh");

#ifndef NDEBUG
	mainScene.printTree();
#endif
}

static void addInputs(Input& input)
{
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
}

static void gameLoop(Window& win, Input& input, ResourceManager& resMan, SceneRoot& mainScene)
{

	win.setVSync(false);
	win.setRelativeMouseMode(true);

	uint64_t lastTick = win.getNanos();
	uint64_t lastLongTick = lastTick;
	uint64_t avgFps = 0;

	constexpr int TICKFREQ = 20; // in Hz

	// single-threaded game loop
	while (win.isRunning()) {

		if (win.getLastFrameStamp() >= lastTick + (BILLION / TICKFREQ)) {
			lastTick = win.getLastFrameStamp();
		}
		if (win.getLastFrameStamp() >= lastLongTick + (BILLION * 5)) {
			lastLongTick = win.getLastFrameStamp();
			avgFps = win.getAvgFPS();
			win.resetAvgFPS();
			win.setTitle(std::to_string(win.getFPS()) + " fps, avg: " + std::to_string(avgFps) + " fps, frames: " + std::to_string(win.getFrameCount()));
		}

		// logic

		if (input.getButtonPress("fullscreen")) {
			if (win.isFullscreen()) {
				win.setFullscreen(false);
			}
			else {
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
			if (win.infoBox("RESOURCES", resMan.getResourcesListString()->c_str()) == false) {
				win.setVSync(!win.getVSync());
			}
		}

		mainScene.updateStuff();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();

	}

}
