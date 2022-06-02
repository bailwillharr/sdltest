#include "sceneroot.hpp"

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

void SceneRoot::updateScene()
{
	updateObjectAndChildren(glm::mat4{1.0f});
}

void SceneRoot::renderScene()
{
	renderObjectAndChildren(glm::mat4{1.0f});
}
