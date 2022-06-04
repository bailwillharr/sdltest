#include "sceneroot.hpp"

#include "custom_component.hpp"

#include "components/camera.hpp"
#include "components/renderer.hpp"

#include <iostream>

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

/*
void SceneRoot::updateScene()
{
	updateObjectAndChildren(glm::mat4{1.0f});
}

void SceneRoot::renderScene()
{
	renderObjectAndChildren(glm::mat4{1.0f});
}*/

void SceneRoot::updateStuff()
{
	// get lists of component types
	// camera
	// renderer
	// custom component

	using namespace components;

	std::vector<Camera> cameras;
	std::vector<Renderer> renderers;
	std::vector<CustomComponent> customComponents;



}
