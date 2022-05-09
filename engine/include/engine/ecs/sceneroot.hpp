#pragma once

#include "engine/ecs/object.hpp"

#include "engine/util/noncopyable.hpp"

#include <utility>
#include <vector>
#include <string>
#include <memory>

namespace engine {
namespace ecs {

// Holds everything you would expect to find in a game scene
class SceneRoot : public Object {

private:
	std::string m_sceneName;

	// a list of the types of components present in the scene
	std::vector<std::string> m_componentTypeList{};

public:
	// create a new empty scene
	SceneRoot(std::string name);
	~SceneRoot();

	void updateScene();
	void renderScene();

};

}}
