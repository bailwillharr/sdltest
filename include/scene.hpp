#pragma once

#include "object.hpp"

#include "util/noncopyable.hpp"

#include <vector>
#include <string>

namespace scene {

// Holds everything you would expect to find in a game scene
class Scene : non_copyable {

private:
	object::Object m_sceneHead;

public:
	Scene();
	~Scene();

};

}
