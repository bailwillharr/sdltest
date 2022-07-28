#include "game.hpp"

#include "config.h"

#include "camera_controller.hpp"
#include "terrain.hpp"
#include "meshgen.hpp"

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

	constexpr float GRASS_DENSITY = 32.0f;
	auto floor = mainScene.createChild("floor");
	auto floorTransform = floor->getComponent<Transform>();
	auto floorRenderer = floor->createComponent<Renderer>();
	floorTransform->position = glm::vec3{ 0.0f, 0.0f, 0.0f };
	floorRenderer->setTexture("textures/stonebrick.png");
	floorRenderer->m_mesh = std::make_unique<resources::Mesh>(std::vector<Vertex>{
		{ { -16.0f, 0.0f, -16.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f,  0.0f  } },
		{ {  16.0f, 0.0f, -16.0f }, { 0.0f, 1.0f, 0.0f }, { GRASS_DENSITY, 0.0f  } },
		{ { -16.0f, 0.0f,  16.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f,  GRASS_DENSITY } },
		{ { -16.0f, 0.0f,  16.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f,  GRASS_DENSITY } },
		{ {  16.0f, 0.0f, -16.0f }, { 0.0f, 1.0f, 0.0f }, { GRASS_DENSITY, 0.0f  } },
		{ {  16.0f, 0.0f,  16.0f }, { 0.0f, 1.0f, 0.0f }, { GRASS_DENSITY, GRASS_DENSITY } }
	});

	auto cam = mainScene.createChild("cam");
	constexpr float HEIGHT_INCHES = 6.0f * 12.0f;
	// eye level is about 4.5 inches below height
	constexpr float EYE_LEVEL = (HEIGHT_INCHES - 4.5f) * 25.4f / 1000.0f;
	cam->getComponent<Transform>()->position = { 0.0f, EYE_LEVEL, 0.0f };
	cam->createComponent<Camera>()->usePerspective(70.0f);
	cam->createComponent<CameraController>();

	auto gun = mainScene.createChild("gun");
	auto gunTransform = gun->getComponent<Transform>();
	auto gunRenderer = gun->createComponent<Renderer>();
	gunTransform->position = glm::vec3{ 1.0f, 5.0f * 12.0f * 25.4f * 0.001f, 1.0f };
	gunTransform->rotation = glm::angleAxis(glm::pi<float>(), glm::vec3{ 0.0f, 1.0f, 0.0f });
	constexpr float GUN_SCALE = 9.0f / 560.0f;
	gunTransform->scale *= GUN_SCALE;
	gunRenderer->setMesh("meshes/gun.mesh");
	gunRenderer->setTexture("textures/gun.png");

	auto tringle = mainScene.createChild("tringle");
	tringle->createComponent<Renderer>()->m_mesh = getChunkMesh(0, 0);
	tringle->getComponent<Transform>()->position = {-2.0f, 0.0f, 0.0f};

	auto chart = mainScene.createChild("chart");
	auto chartTransform = chart->getComponent<Transform>();
	auto chartRenderer = chart->createComponent<Renderer>();
	chartRenderer->m_mesh = std::make_unique<resources::Mesh>(std::vector<Vertex>{
		{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f  } },
		{ { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f  } },
		{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
		{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
		{ { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f  } },
		{ { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } }
	});
	chartRenderer->setTexture("textures/ten_feet.png");
	chartTransform->scale = {1.0f, 10.0f * 12.0f * 25.4f * 0.001f, 1.0f};
	chartTransform->position = {1.0f, 0.0f, 1.0f};
	chartTransform->rotation = glm::angleAxis(glm::half_pi<float>(), glm::vec3{0.0f, 1.0f, 0.0f});

	mainScene.createChild("sphere")->createComponent<Renderer>()->m_mesh = genSphereMesh(1.0f, 32);
	mainScene.getChild("sphere")->getComponent<Renderer>()->setTexture("textures/stonebrick.png");
	mainScene.getChild("sphere")->getComponent<Transform>()->position = {0.0f, 1.0f, 0.0f};

#ifndef NDEBUG
	mainScene.printTree();
#endif
}

static void addInputs(Input& input)
{
	// menu, settings controls
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

	win.setVSync(true);
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

		if (win.getKeyPress(inputs::Key::F11)) {
			if (win.isFullscreen()) {
				win.setFullscreen(false);
			}
			else {
				//win.setFullscreen(true, false); // disable exclusive mode, use borderless window
				win.setFullscreen(true, true); // use exclusive fullscreen
			}
		}
		if (win.getKeyPress(inputs::Key::Q)) {
			bool captured = win.mouseCaptured();
			win.setRelativeMouseMode(!captured);
			input.setDeviceActive(InputDevice::MOUSE, !captured);
		}
		if (input.getButtonPress("quit"))
			win.setCloseFlag();
		if (win.getKeyPress(inputs::Key::TAB)) {
			win.infoBox("RESOURCES", resMan.getResourcesListString()->c_str());
		}
		if (win.getKeyPress(inputs::Key::V)) {
			win.setVSync(!win.getVSync());
		}

		mainScene.updateStuff();

		// swap
		win.swapBuffers();

		// events
		win.getInputAndEvents();

	}

}
