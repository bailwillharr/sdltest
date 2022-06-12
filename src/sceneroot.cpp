#include "sceneroot.hpp"

#include "components/custom.hpp"
#include "components/camera.hpp"
#include "components/renderer.hpp"

#include <glm/mat4x4.hpp>

#include <iostream>
#include <tuple>

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
	// TODO
	// Get list of all components with corresponding transform matrices
	// Only then, do these updates

	using namespace components;
	using namespace glm;

	struct CompList compList{};

	getAllSubComponents(compList, glm::mat4{1.0f});

/*
	std::cerr << "Cameras:\n";
	for (const auto& [c, t] : compList.cameras) {
		std::cerr << "ID: " << c->getID() << "\t\t x: " << t[3][0] << " y: " << t[3][1] << " z: " << t[3][2] << "\n";
	}
	std::cerr << "Renderers:\n";
	for (const auto& [c, t] : compList.renderers) {
		std::cerr << "ID: " << c->getID() << "\t\t x: " << t[3][0] << " y: " << t[3][1] << " z: " << t[3][2] << "\n";
	}
	std::cerr << "Custom Components:\n";
	for (const auto& [c, t] : compList.customs) {
		std::cerr << "ID: " << c->getID() << "\t\t x: " << t[3][0] << " y: " << t[3][1] << " z: " << t[3][2] << "\n";
	}
*/

	// update
	
	for (const auto [c, t] : compList.customs) {
		c->onUpdate(t);
	}

	// render

	for (const auto [c, t] : compList.cameras) {
		if (c->isActive()) {
			c->updateCam(t);
		}
	}

	for (const auto [c, t] : compList.renderers) {
		c->render(t);
	}

}
