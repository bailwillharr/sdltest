#include "sceneroot.hpp"

#include "components/custom.hpp"
#include "components/camera.hpp"
#include "components/renderer.hpp"

#include <glm/mat4x4.hpp>

#include <iostream>

SceneRoot::SceneRoot(struct GameIO things) : Object("root", nullptr, things)
{
#ifndef NDEBUG
	std::cerr << "Empty SceneRoot has been constructed\n";
#endif
}

SceneRoot::SceneRoot(const std::filesystem::path& file, struct GameIO things) : SceneRoot(things)
{
	// TODO: make this a resource
	//loadFromSceneFile(file);
}

SceneRoot::~SceneRoot()
{
#ifndef NDEBUG
	std::cerr << "SceneRoot class destroyed\n";
#endif
}

// private methods

// public methods

void SceneRoot::updateStuff()
{

	using namespace components;
	using namespace glm;

	struct CompList compList{};

	getAllSubComponents(compList, glm::mat4{1.0f});

	// update
	
	for (const auto& [c, t] : compList.customs) {
		c->onUpdate(t);
	}

	// render

	for (const auto& [c, t] : compList.cameras) {
		if (c->isActive()) {
			c->updateCam(t);
		}
	}

	for (const auto& [c, t] : compList.renderers) {
		c->render(t);
	}

}
