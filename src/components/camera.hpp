#pragma once

#include "component.hpp"

#include "object.hpp"

#include <vector>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace components {

class Camera : public Component {

private:
	enum class Modes {
		PERSPECTIVE,
		M_2D
	};

	Modes m_mode = Modes::M_2D;

	// perspective mode settings
	float m_fovDeg = 90.0f;

	glm::mat4 m_projMatrix{ 1.0f };

	static int s_activeCamera;

public:
	Camera(Object* parent);

	// called every frame, don't call manually
	void updateCam(glm::mat4 transform);

	void makeActive();
	bool isActive();

	void usePerspective(float fovDeg);
	void use2D();

};

}
