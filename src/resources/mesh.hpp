#pragma once

#include "resource.hpp"

#include "resources/shader.hpp"

#include <glad/glad.h>

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

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	static int s_active_vao;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	void bindVAO() const;

public:
	Mesh(const std::filesystem::path& resPath);
	~Mesh() override;

	void drawMesh(const Shader& shader);

};

}
