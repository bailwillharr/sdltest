#pragma once

#include "component.hpp"

#include "object.hpp"

#include <vector>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace components {

class Camera : public Component {

private:
	glm::mat4 m_viewMatrix{ 1.0f };
	glm::mat4 m_projMatrix{ 1.0f };

public:
	Camera(Object* parent);
	void onUpdate(glm::mat4 transform) override;
	void onRender(glm::mat4 transform) override;
};

}
