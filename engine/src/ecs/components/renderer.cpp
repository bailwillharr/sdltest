#include "engine/ecs/components/renderer.hpp"

#include <iostream>

namespace engine {
namespace ecs {
namespace components {

Renderer::Renderer(ecs::Object* parent) : Component(parent, "renderer")
{

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_mesh->getVerticesSize(), m_mesh->getVerticesPtr(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	std::vector<unsigned int> tmpIndices{};
	for (int i = 0; i < (int)m_mesh->getVerticesSize(); i++) {
		tmpIndices.push_back(i);
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh->getVerticesSize(), &(tmpIndices[0]), GL_STATIC_DRAW);

	//glEnableVertexAttribArray(m_material->getAttribLocation("v_Pos"), )

}

Renderer::~Renderer()
{

}

void Renderer::onUpdate(glm::mat4 transform)
{
	(void)transform;
}

void Renderer::onRender(glm::mat4 transform)
{
	if (m_material->setUniform("model", transform) != true) {
		throw std::runtime_error("Unable to find 'model' uniform in shader");
	}
}

}}}
