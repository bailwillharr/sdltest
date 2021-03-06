#pragma once

#include "resource.hpp"

#include "resources/shader.hpp"

#include <glad/glad.h>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <memory>

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 uv;
};

namespace resources {

class Mesh : public Resource {

public:
	Mesh(const std::vector<Vertex>& vertices);
	Mesh(const std::filesystem::path& resPath);
	~Mesh() override;

	void drawMesh(const Shader& shader);

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

private:
	static int s_active_vao;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	void bindVAO() const;

	void initMesh();

};

}
