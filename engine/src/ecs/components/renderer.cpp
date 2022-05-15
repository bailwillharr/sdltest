#include "engine/ecs/components/renderer.hpp"

#include <iostream>

namespace engine {
namespace ecs {
namespace components {

Renderer::Renderer(ecs::Object* parent) : Component(parent, "renderer"), m_shader(std::make_shared<rendering::Shader>("basic"))
{
	std::cout << "Uniforms:\n";
	for (const rendering::Uniform& uniform : m_shader->getUniforms()) {
		std::cout << "\tname: " << uniform.name << " size: " << uniform.size << " type: " << static_cast<int>(uniform.type) << "\n";
	}
}

Renderer::~Renderer()
{

}

}}}
