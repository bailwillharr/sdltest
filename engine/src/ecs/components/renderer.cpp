#include "engine/ecs/components/renderer.hpp"

#include <iostream>

namespace engine {
namespace ecs {
namespace components {

GLuint Renderer::s_active_vao = 0;

void Renderer::bindVAO()
{
	if (s_active_vao != m_vao) {
		glBindVertexArray(m_vao);
		s_active_vao = m_vao;
	}
}

void Renderer::drawMesh()
{
	bindVAO();
	m_shader->makeActive();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_mesh->getNumVertices()), GL_UNSIGNED_INT, 0);
}

Renderer::Renderer(ecs::Object* parent) : Component(parent, "renderer")
{

	m_mesh->m_vertices.push_back({	{0.0f, 0.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{0.0f, 1.0f} });
	m_mesh->m_vertices.push_back({	{1.0f, 0.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{1.0f, 1.0f} });
	m_mesh->m_vertices.push_back({	{0.0f, 1.0f, 0.0f},		{0.0f, 0.0f, -1.0f},	{0.0f, 0.0f} });

	glGenVertexArrays(1, &m_vao);
	bindVAO();
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
	glEnableVertexAttribArray(m_shader->getAttribLocation("v_Position"));
	glVertexAttribPointer(m_shader->getAttribLocation("v_Position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(m_shader->getAttribLocation("v_Normal"));
	//glVertexAttribPointer(m_shader->getAttribLocation("v_Normal"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)3);
	//glEnableVertexAttribArray(m_shader->getAttribLocation("v_UV"));
	//glVertexAttribPointer(m_shader->getAttribLocation("v_UV"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)6);
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

	m_shader->setUniform("color", { 0.2f, 0.4f, 0.0f });
	m_shader->setUniform("modelMat", transform );

	drawMesh();

}

}}}
