#include "rendering/mesh.hpp"

namespace rendering {

size_t Mesh::getNumVertices() const
{
	return m_vertices.size();
}

const void * Mesh::getVerticesPtr() const
{
	return &(m_vertices[0].pos[0]);
}

}
