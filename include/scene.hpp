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

public:
	// create a new empty scene
	Scene(std::string name);
	~Scene();

	std::weak_ptr<object::Object> getRoot();

};

}
