#include "resources/mesh.hpp"
#include <iostream>

namespace resources {

GLuint Mesh::s_active_vao = 0;

void Mesh::bindVAO() const
{
	if (s_active_vao != m_vao) {
		glBindVertexArray(m_vao);
		s_active_vao = m_vao;
	}
}

void Mesh::drawMesh(const Shader& shader)
{
	bindVAO();
	shader.makeActive();
#ifndef SDLTEST_NOGFX
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(getNumVertices()), GL_UNSIGNED_INT, 0);
#endif
}

Mesh::Mesh(const std::filesystem::path& resPath) : Resource(resPath)
{

	// call model loading functions here

	m_vertices.push_back({ {0.0f, 0.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{0.0f, 1.0f} });
	m_vertices.push_back({ {1.0f, 0.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{1.0f, 1.0f} });
	m_vertices.push_back({ {0.0f, 1.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{0.0f, 0.0f} });

	glGenVertexArrays(1, &m_vao);
	bindVAO();
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, getNumVertices()*sizeof(resources::Vertex), getVerticesPtr(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	std::vector<unsigned int> tmpIndices{};
	for (int i = 0; i < (int)getNumVertices(); i++) {
		tmpIndices.push_back(i);
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, getNumVertices()*sizeof(resources::Vertex), &(tmpIndices[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

size_t Mesh::getNumVertices() const
{
	return m_vertices.size();
}

const void * Mesh::getVerticesPtr() const
{
	return &(m_vertices[0].pos[0]);
}

}
