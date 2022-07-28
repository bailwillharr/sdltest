#pragma once

#include "resources/mesh.hpp"

// generates a UV sphere
std::unique_ptr<resources::Mesh> genSphereMesh(float r, int detail);
