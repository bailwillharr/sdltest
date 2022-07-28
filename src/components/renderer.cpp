#include "components/renderer.hpp"

#include "object.hpp"

#include "resource_manager.hpp"

#include <iostream>

namespace components {

Renderer::Renderer(Object* parent) : Component(parent, TypeEnum::RENDERER)
{
	m_shader = this->parent.res.get<resources::Shader>("shaders/basic.glsl");
	m_texture = this->parent.res.get<resources::Texture>("textures/missing.png");

	m_shader->setUniform("lightPos", { 1000.0f, 1000.0f, 400.0f });
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
