#pragma once

#include "components/custom.hpp"

namespace components {
	class Transform;
}

class CameraController : public components::CustomComponent {

public:
	CameraController(Object* parent);
	void onUpdate(glm::mat4 t) override;

private:
	components::Transform* tcomp;
	float m_yaw = 0.0f;
	float m_pitch = 0.0f;

};
