#include "scene.hpp"

#include <iostream>

namespace scene {

Scene::Scene(std::string name) : m_sceneRoot(new object::Object("root")), m_name(name)
{

}

Scene::~Scene()
{
	std::cout << "Scene class destructor: " << m_name << "\n";
}


std::shared_ptr<object::Object> Scene::getRoot()
{
	return m_sceneRoot;
}

}
