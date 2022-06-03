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

	static int s_activeCamera;

public:
	Camera(Object* parent);
	void updateCam(glm::mat4 transform);

	void makeActive();

};

}
