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
	glBufferData(GL_ARRAY_BUFFER, m_mesh->getNumVertices()*sizeof(rendering::Vertex), m_mesh->getVerticesPtr(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	std::vector<unsigned int> tmpIndices{};
	for (int i = 0; i < (int)m_mesh->getNumVertices(); i++) {
		tmpIndices.push_back(i);
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh->getNumVertices()*sizeof(rendering::Vertex), &(tmpIndices[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(m_material->getAttribLocation("v_Position"));
	glVertexAttribPointer(m_material->getAttribLocation("v_Position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(m_material->getAttribLocation("v_Normal"));
	//glVertexAttribPointer(m_material->getAttribLocation("v_Normal"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)3);
	//glEnableVertexAttribArray(m_material->getAttribLocation("v_UV"));
	//glVertexAttribPointer(m_material->getAttribLocation("v_UV"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)6);
	glBindVertexArray(0);
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
	glBindVertexArray(m_vao);
	if (m_material->setUniform("model", transform) != true) {
		throw std::runtime_error("Unable to find 'model' uniform in shader");
	}
	glDrawElements(GL_TRIANGLES, m_mesh->getNumVertices(), GL_UNSIGNED_INT, 0);
}

}}}
