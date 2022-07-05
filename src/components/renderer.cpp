#include "components/renderer.hpp"

#include "object.hpp"

#include "resource_manager.hpp"

#include <iostream>

namespace components {

Renderer::Renderer(Object* parent) : Component(parent, TypeEnum::RENDERER)
{
	m_shader = this->parent.res.get<resources::Shader>("basic.glsl");
	m_texture = this->parent.res.get<resources::Texture>("missing.glraw");

	m_shader->setUniform("lightPos", { 3.0f, 100.0f, 0.0f });
}

Renderer::~Renderer()
{

}

void Renderer::render(glm::mat4 transform)
{
	m_shader->setUniform("modelMat", transform );
	m_texture->bindTexture();
	m_mesh->drawMesh(*m_shader);
}

void Renderer::setMesh(const std::string& name)
{
	m_mesh = parent.res.get<resources::Mesh>(name);
}

void Renderer::setTexture(const std::string& name)
{
	m_texture = parent.res.get<resources::Texture>(name);
}

}
