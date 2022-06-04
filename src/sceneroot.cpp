#include "sceneroot.hpp"

#include "custom_component.hpp"

#include "components/camera.hpp"
#include "components/renderer.hpp"

#include <glm/mat4x4.hpp>

#include <iostream>
#include <tuple>

SceneRoot::SceneRoot(std::string name, struct GameIO things) : Object("root", nullptr, things), m_sceneName(name)
{
#ifdef SDLTEST_DEBUG
	std::cerr << "SceneRoot '" << m_sceneName << "' has been constructed\n";
#endif
}

SceneRoot::~SceneRoot()
{
#ifdef SDLTEST_DEBUG
	std::cerr << "SceneRoot class destroyed: '" << m_sceneName << "'\n";
#endif
}

// private methods

// public methods

void SceneRoot::updateStuff()
{
	// get lists of component types
	// camera
	// renderer
	// custom component

	using namespace components;
	using namespace glm;

	ComponentLists lists{}; // initialised to empty vectors
	
	getComponentLists(lists, glm::mat4{1.0f});

	for (const auto& [camera, t] : lists.cameras) {
		camera->updateCam(t);
	}

	for (const auto& [comp, t] : lists.customComponents) {

	}

	for (const auto& [renderer, t] : lists.renderers) {
		renderer->render(t);
	}



}
