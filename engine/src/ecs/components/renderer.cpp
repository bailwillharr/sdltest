#include "engine/ecs/components/renderer.hpp"

#include <iostream>

namespace engine {
namespace ecs {
namespace components {

Renderer::Renderer(ecs::Object* parent) : Component(parent, "renderer")
{
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
