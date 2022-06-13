#pragma once

#include "object.hpp"

#include <filesystem>

// Holds everything you would expect to find in a game scene
class SceneRoot : public Object {

private:

public:
	// create a new empty scene
	SceneRoot(struct GameIO things);
	SceneRoot(const std::filesystem::path& file, struct GameIO things);

	SceneRoot(const SceneRoot&) = delete;
	SceneRoot& operator=(const SceneRoot&) = delete;
	~SceneRoot();

	void updateStuff();

};
