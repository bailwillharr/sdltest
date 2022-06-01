#include "resources/mesh.hpp"

namespace resources {

Mesh::Mesh(const std::filesystem::path& resPath) : Resource(resPath)
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

}
