#include "game/camera_controller.hpp"

#include "object.hpp"

#include "components/transform.hpp"

#include "window.hpp"
#include "input.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

CameraController::CameraController(Object* parent) :
	CustomComponent(parent)
{
	tcomp = this->parent.getComponent<components::Transform>();

	tcomp->position.x -= 2.0f;
}

void CameraController::onUpdate(glm::mat4 t)
{

	// calculate new position

	const float dt = win.dt();
	constexpr float SPEED = 10.0f;

	const float dx = inp.getAxis("movex") * SPEED;
	//const float dy = ((inp.getButton("jump") ? 10.0f : 0.0f) - (inp.getButton("sneak") ? 10.0f : 0.0f)) * SPEED;
	const float dy = 0.0f;
	const float dz = (-inp.getAxis("movey")) * SPEED;

	// calculate new pitch and yaw

	constexpr float MAX_PITCH = glm::half_pi<float>();
	constexpr float MIN_PITCH = -MAX_PITCH;

	float dPitch = inp.getAxis("looky") * -0.002f;
	m_pitch += dPitch;
	if (m_pitch <= MIN_PITCH || m_pitch >= MAX_PITCH) {
		m_pitch -= dPitch;
	}
	m_yaw += inp.getAxis("lookx") * -0.002f;

	// update position relative to camera direction in xz plane
	const glm::vec3 d2xRotated = glm::rotateY(glm::vec3{ dx, 0.0f, 0.0f }, m_yaw);
	const glm::vec3 d2zRotated = glm::rotateY(glm::vec3{ 0.0f, 0.0f, dz }, m_yaw);
	tcomp->position += (d2xRotated + d2zRotated) * dt;
	tcomp->position.y += dy * dt;

	// pitch quaternion
	const float halfPitch = m_pitch / 2.0f;
	glm::quat pitchQuat;
	pitchQuat.x = glm::sin(halfPitch);
	pitchQuat.y = 0.0f;
	pitchQuat.z = 0.0f;
	pitchQuat.w = glm::cos(halfPitch);

	// yaw quaternion
	const float halfYaw = m_yaw / 2.0f;
	glm::quat yawQuat;
	yawQuat.x = 0.0f;
	yawQuat.y = glm::sin(halfYaw);
	yawQuat.z = 0.0f;
	yawQuat.w = glm::cos(halfYaw);

	// update rotation
	tcomp->rotation = yawQuat * pitchQuat;

}
