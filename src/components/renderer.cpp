#include "components/renderer.hpp"

#include "object.hpp"

#include <iostream>

namespace components {

Renderer::Renderer(Object* parent) : Component(parent, TypeEnum::RENDERER)
{
	m_shader = parent->resMan()->get<resources::Shader>("basic.glsl");
	m_mesh = parent->resMan()->get<resources::Mesh>("gun.mesh");
}

Renderer::~Renderer()
{

}

void Renderer::render(glm::mat4 transform)
{
	m_shader->setUniform("color", { 0.2f, 0.4f, 0.0f });
	m_shader->setUniform("modelMat", transform );
	m_mesh->drawMesh(*m_shader);
}

void Renderer::setMesh(const std::string& name)
{
	m_mesh = m_parent->resMan()->get<resources::Mesh>(name);
}

}
