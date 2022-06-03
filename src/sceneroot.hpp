#pragma once

#include "object.hpp"

#include "components/camera.hpp"
#include "components/renderer.hpp"

#include <utility>
#include <vector>
#include <string>
#include <memory>

// Holds everything you would expect to find in a game scene
class SceneRoot : public Object {

private:
	std::string m_sceneName;

public:
	// create a new empty scene
	SceneRoot(std::string name, struct GameIO things);
	SceneRoot(const SceneRoot&) = delete;
	SceneRoot& operator=(const SceneRoot&) = delete;
	~SceneRoot();

	void updateStuff();

};
