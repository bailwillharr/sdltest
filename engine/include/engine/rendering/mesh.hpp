#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <memory>

namespace engine {
namespace rendering {

class Mesh {
private:

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 norm;
		glm::vec2 uv;
	};

	std::vector<Vertex> m_vertices;

public:
	Mesh();
	~Mesh();

	size_t getVerticesSize() const;
	const void * getVerticesPtr() const;

};

}}
