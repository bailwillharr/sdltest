#pragma once

#include "engine/ecs/component.hpp"

#include "engine/resource/shader.hpp"
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

	std::shared_ptr<engine::resource::Shader> m_shader;
	std::shared_ptr<engine::rendering::Mesh> m_mesh = std::make_shared<engine::rendering::Mesh>();

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	void bindVAO();
	void drawMesh();

public:
	Renderer(ecs::Object*);
	~Renderer() override;

	void onUpdate(glm::mat4 transform) override;
	void onRender(glm::mat4 transform) override;
	
};

}}}
