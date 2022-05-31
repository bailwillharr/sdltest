#pragma once

#include "component.hpp"

#include "resources/shader.hpp"
#include "rendering/mesh.hpp"

#include <vector>
#include <string>
#include <memory>

namespace components {

class Renderer : public Component {

private:
	static GLuint s_active_vao;

	std::shared_ptr<resources::Shader> m_shader;
	std::shared_ptr<rendering::Mesh> m_mesh = std::make_shared<rendering::Mesh>();

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	void bindVAO();
	void drawMesh();

public:
	Renderer(Object*);
	~Renderer() override;

	void onUpdate(glm::mat4 transform) override;
	void onRender(glm::mat4 transform) override;
	
};

}
