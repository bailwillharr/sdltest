#include "ecs/sceneroot.hpp"

#include <iostream>

namespace engine {
namespace ecs {

SceneRoot::SceneRoot(std::string name) : Object("root"), m_sceneName(name)
{
	std::cerr << "SceneRoot '" << m_sceneName << "' has been constructed\n";
}

SceneRoot::~SceneRoot()
{
	std::cerr << "SceneRoot class destroyed: '" << m_sceneName << "'\n";
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

}}
