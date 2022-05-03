#include "scene.hpp"

#include <iostream>
#include <type_traits>

namespace scene {

Scene::Scene(std::string name) : m_sceneRoot(new object::Object("root")), m_name(name)
{

}

Scene::~Scene()
{

}

// private methods

// public methods

std::shared_ptr<object::Object> Scene::getRoot()
{
	return m_sceneRoot;
}

}
