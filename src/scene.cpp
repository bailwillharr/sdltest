#include "scene.hpp"

#include "object.hpp"

#include <iostream>

namespace scene {

Scene::Scene(std::string name) : m_sceneRoot(std::make_shared<object::Object>("root")), m_name(name)
{
	std::cout << "Scene '" << name << "' has been constructed\n";
}

Scene::~Scene()
{
	std::cout << "Scene class destroyed: '" << m_name << "'\n";
}

// private methods

// public methods

std::weak_ptr<object::Object> Scene::getRoot()
{
	return m_sceneRoot;
}

}
