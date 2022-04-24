#pragma once

#include "object.hpp"

#include "util/noncopyable.hpp"

#include <utility>
#include <vector>
#include <string>
#include <memory>

namespace scene {

// Holds everything you would expect to find in a game scene
class Scene : non_copyable {

private:
	std::shared_ptr<object::Object> m_sceneRoot;
	std::string m_name;

	// A table containing pointers to ComponentCacheEntries
	std::vector<std::pair<std::string, std::vector<std::shared_ptr<component::ComponentCacheBase>>>> m_cache;

	void genCacheEntriesFromObject(std::shared_ptr<object::Object> obj);

public:
	// create a new empty scene
	Scene(std::string name);
	~Scene();

	std::shared_ptr<object::Object> getRoot();

	// Cache the required matrices and other data for the components present
	// in the scene.
	void genSceneCache();

	void printCache();

};

}
