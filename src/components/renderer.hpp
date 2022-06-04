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

	std::shared_ptr<resources::Shader> m_shader;
	std::shared_ptr<resources::Mesh> m_mesh;

public:
	Renderer(Object*);
	~Renderer() override;

	void render(glm::mat4 transform);
	
};

}
