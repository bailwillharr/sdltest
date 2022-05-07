#include "engine/ecs/sceneroot.hpp"

#include <iostream>

namespace engine {
namespace ecs {

SceneRoot::SceneRoot(std::string name) : Object("root"), m_sceneName(name)
{
	std::cout << "SceneRoot '" << m_sceneName << "' has been constructed\n";
}

SceneRoot::~SceneRoot()
{
	std::cout << "SceneRoot class destroyed: '" << m_sceneName << "'\n";
}

// private methods

// public methods

}}
