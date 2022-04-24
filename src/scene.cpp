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

void Scene::genCacheEntriesFromObject(std::shared_ptr<object::Object> obj)
{
	for (auto &comp : obj->getComponents()) {
		bool found = false;
		for (auto &pair : m_cache) {
			if (pair.first == comp->getTypeName()) {
				found = true;
				pair.second.push_back(comp->getCacheEntry());
			}
		}
		if (found == false) {
			m_cache.emplace_back(comp->getTypeName(), 0);
		}
	}
}

// public methods

std::shared_ptr<object::Object> Scene::getRoot()
{
	return m_sceneRoot;
}

void Scene::genSceneCache()
{
	genCacheEntriesFromObject(m_sceneRoot);
}

void Scene::printCache()
{
}

}
