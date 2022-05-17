#include "engine/rendering/mesh.hpp"

namespace engine {
namespace rendering {

Mesh::Mesh()
{
	m_vertices.push_back({ {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} });
	m_vertices.push_back({ {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} });
	m_vertices.push_back({ {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} });
}

Mesh::~Mesh()
{

}

size_t Mesh::getNumVertices() const
{
	return m_vertices.size();
}

const void * Mesh::getVerticesPtr() const
{
	return &(m_vertices[0].pos[0]);
}

}}
