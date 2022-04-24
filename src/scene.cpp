#include "scene.hpp"

namespace scene {

Scene::Scene() : m_sceneRoot(new object::Object("root"))
{

}

Scene::~Scene()
{

}


std::shared_ptr<object::Object> Scene::getRoot()
{
	return m_sceneRoot;
}

}
