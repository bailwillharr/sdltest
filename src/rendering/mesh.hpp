#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <memory>

namespace rendering {

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 uv;
};

struct Mesh {

	std::vector<Vertex> m_vertices;

	size_t getNumVertices() const;
	const void * getVerticesPtr() const;

};

}
