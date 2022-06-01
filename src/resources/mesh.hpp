#pragma once

#include "resource.hpp"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <memory>

namespace resources {

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 uv;
};

class Mesh : public Resource {

public:
	Mesh(const std::filesystem::path& resPath);
	~Mesh() = default;

	std::vector<Vertex> m_vertices;

	size_t getNumVertices() const;
	const void * getVerticesPtr() const;

};

}
