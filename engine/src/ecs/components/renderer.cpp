#include "engine/ecs/components/renderer.hpp"

#include <iostream>

namespace engine {
namespace ecs {
namespace components {

Renderer::Renderer(ecs::Object* parent) : Component(parent, "renderer"), m_shader(std::make_shared<rendering::Shader>("basic"))
{
}

Renderer::~Renderer()
{

}

}}}
