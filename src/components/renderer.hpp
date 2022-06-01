#pragma once

#include "component.hpp"

#include "resources/shader.hpp"
#include "resources/mesh.hpp"

#include <vector>
#include <string>
#include <memory>

namespace components {

class Renderer : public Component {

private:
	static GLuint s_active_vao;

	std::shared_ptr<resources::Shader> m_shader;
	std::shared_ptr<resources::Mesh> m_mesh;

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
