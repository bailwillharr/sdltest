#include "game.hpp"

#include "config.h"

#include "camera_controller.hpp"

#include "window.hpp"
#include "input.hpp"
#include "resource_manager.hpp"
#include "sceneroot.hpp"

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
	mainScene.createChild("floor")->createComponent<components::Renderer>()->setMesh("floor.mesh");
	mainScene.getChild("floor")->getComponent<components::Renderer>()->setTexture("floor.glraw");
	mainScene.getChild("floor")->getComponent<components::Transform>()->scale = glm::vec3{128.0f, 1.0f, 128.0f};
	mainScene.getChild("floor")->getComponent<components::Transform>()->position = glm::vec3{ 0.0f, 0.0f, 0.0f };

	mainScene.createChild("cam")->createComponent<components::Camera>()->usePerspective(70.0f);
	mainScene.getChild("cam")->createComponent<CameraController>();
	mainScene.getChild("cam")->getComponent<components::Transform>()->position = { 0.0f, 50.0f, 0.0f };
	mainScene.getChild("cam")->createChild("gun")->createComponent<components::Renderer>()->setMesh("gun.mesh");
	mainScene.getChild("cam")->getChild("gun")->getComponent<components::Transform>()
		->position = glm::vec3{ 3.0f, -10.0f, -10.0f };
	mainScene.getChild("cam")->getChild("gun")->getComponent<components::Transform>()
		->rotation = glm::angleAxis(glm::pi<float>(), glm::vec3{ 0.0f, 1.0f, 0.0f });

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
			win.setTitle(std::to_string(win.getFPS()) + " fps, avg: " + std::to_string(avgFps) + " fps, frames: " + std::to_string(win.getFrameCount()));
		}
		if (win.getLastFrameStamp() >= lastLongTick + (BILLION * 5)) {
			lastLongTick = win.getLastFrameStamp();
			avgFps = win.getAvgFPS();
			win.resetAvgFPS();
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
