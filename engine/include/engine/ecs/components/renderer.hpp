#pragma once

#include "engine/ecs/component.hpp"

#include "engine/resource/material.hpp"
#include "engine/rendering/mesh.hpp"

#include <vector>
#include <string>
#include <memory>

namespace engine {
namespace ecs {
namespace components {

class Renderer : public Component {

private:
	static GLuint s_active_vao;

	std::shared_ptr<engine::resource::Material> m_material = std::make_shared<engine::resource::Material>();
	std::shared_ptr<engine::rendering::Mesh> m_mesh = std::make_shared<engine::rendering::Mesh>();
//	std::shared_ptr<engine::rendering::Material> m_material;
//	std::shared_ptr<engine::rendering::Mesh> m_mesh;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	void bindVAO();

public:
	Renderer(ecs::Object*);
	~Renderer() override;

	void onUpdate(glm::mat4 transform) override;
	void onRender(glm::mat4 transform) override;
	
};

}}}
