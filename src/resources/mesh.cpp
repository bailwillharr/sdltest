#include "resources/mesh.hpp"
#include <iostream>

namespace resources {

struct MeshFileHeader {
	unsigned int vertex_count;
	unsigned int index_count;
	int material;
};

static void loadMeshFromFile(const std::filesystem::path& path, std::vector<Vertex>* vertices, std::vector<unsigned int>* indices)
{

	// TODO
	// Replace this aberation with something that's readable and doesn't use FILE*

	struct MeshFileHeader header{};

	FILE* fp = fopen(path.string().c_str(), "rb");

	fread(&header, sizeof(struct MeshFileHeader), 1, fp);

	indices->resize(header.index_count);
	vertices->resize(header.vertex_count);

	fread(&(*indices)[0], sizeof(unsigned int) * header.index_count, 1, fp);
	fread(&((*vertices)[0].pos[0]), sizeof(float) * 8 * header.vertex_count, 1, fp);

	fclose(fp);
}

// -1 means invalidated
int Mesh::s_active_vao = -1;

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
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
#endif
}

Mesh::Mesh(const std::filesystem::path& resPath) : Resource(resPath, "mesh")
{
	
	loadMeshFromFile(resPath, &m_vertices, &m_indices);

	/*
	m_vertices.push_back({ {0.0f, 0.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{0.0f, 1.0f} });
	m_vertices.push_back({ {1.0f, 0.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{1.0f, 1.0f} });
	m_vertices.push_back({ {0.0f, 1.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{0.0f, 0.0f} });
	m_indices.push_back(0);
	m_indices.push_back(1);
	m_indices.push_back(2);
	*/

	glGenVertexArrays(1, &m_vao);
	bindVAO();
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(resources::Vertex), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &(m_indices[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex, norm));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex, uv));
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	if (s_active_vao == m_vao) {
		s_active_vao = -1;
	}
}

}
