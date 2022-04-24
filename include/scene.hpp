#pragma once

#include "object.hpp"

#include "util/noncopyable.hpp"

#include <vector>
#include <string>
#include <memory>

namespace scene {

// Holds everything you would expect to find in a game scene
class Scene : non_copyable {

private:
	std::shared_ptr<object::Object> m_sceneRoot;

public:
	Scene();
	~Scene();

	std::shared_ptr<object::Object> getRoot();

};

}
