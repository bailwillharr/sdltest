#pragma once

#include "engine/ecs/component.hpp"

#include "engine/rendering/material.hpp"

#include <vector>
#include <string>
#include <memory>

namespace engine {
namespace ecs {
namespace components {

class Renderer : public Component {

private:
	std::shared_ptr<engine::rendering::Material> m_material = std::make_shared<engine::rendering::Material>();

public:
	Renderer(ecs::Object*);
	~Renderer() override;

	void onUpdate(glm::mat4 transform) override;
	void onRender(glm::mat4 transform) override;
	
};

}}}
