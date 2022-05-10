#pragma once

#include "engine/ecs/component.hpp"

#include "engine/rendering/shader.hpp"

#include <vector>
#include <string>
#include <memory>

namespace engine {
namespace ecs {
namespace components {

class Renderer : public Component {

private:
	std::shared_ptr<engine::rendering::Shader> m_shader;

public:
	Renderer(ecs::Object*);
	~Renderer() override;
	
};

}}}
