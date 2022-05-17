#include "engine/rendering/mesh.hpp"

namespace engine {
namespace rendering {

Mesh::Mesh()
{
	m_vertices.push_back({ glm::vec3(1.0f), glm::vec3(1.0f), glm::vec2(1.0f) });
	m_vertices.push_back({ {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} });
	m_vertices.push_back({ {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} });
	m_vertices.push_back({ {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} });
}

Mesh::~Mesh()
{

}

size_t Mesh::getVerticesSize() const
{
	return m_vertices.size() * sizeof(Vertex);
}

const void * Mesh::getVerticesPtr() const
{
	return &(m_vertices[0].pos[0]);
}

}}
