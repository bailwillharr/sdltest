#include "components/renderer.hpp"

#include "object.hpp"

#include <iostream>

namespace components {

Renderer::Renderer(Object* parent) : Component(parent, "renderer")
{
	m_shader = parent->resMan()->get<resources::Shader>("basic.glsl");
	m_mesh = parent->resMan()->get<resources::Mesh>("triangle.mesh");
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

	m_mesh->drawMesh(*m_shader);

}

}
