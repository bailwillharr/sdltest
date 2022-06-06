#include "components/camera.hpp"

#include "resources/shader.hpp"

static const std::string VIEW_MAT_UNIFORM = "viewMat";
static const std::string PROJ_MAT_UNIFORM = "projMat";

namespace components {

// -1 means no active camera
int Camera::s_activeCamera = -1;

Camera::Camera(Object* parent) : Component(parent, TypeEnum::CAMERA)
{
	// if no other active camera, make this one active
	if (s_activeCamera == -1) makeActive();

	glEnable(GL_DEPTH_TEST);
}

void Camera::updateCam(glm::mat4 transform)
{

	if (m_mode == Modes::PERSPECTIVE) {
		if (m_parent->window()->getWindowResized()) {
			usePerspective(m_fovDeg);
		}
	}

	glm::mat4 viewMatrix = glm::inverse(transform);

	using namespace resources;

	auto resPtrs = m_parent->resMan()->getAllResourcesOfType("shader");
	for (const auto& resPtr : resPtrs) {
		// shader ref count increased by 1, but only in this scope
		auto lockedPtr = resPtr.lock();
		auto shader = dynamic_cast<Shader*>(lockedPtr.get());
		if (shader->getUniformType(VIEW_MAT_UNIFORM) == Shader::UniformType::FLOAT_MAT4 &&
			shader->getUniformType(PROJ_MAT_UNIFORM) == Shader::UniformType::FLOAT_MAT4) {
			shader->setUniform(VIEW_MAT_UNIFORM, viewMatrix);
			shader->setUniform(PROJ_MAT_UNIFORM, m_projMatrix);
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Camera::makeActive()
{
	s_activeCamera = getID();
}

bool Camera::isActive()
{
	return (s_activeCamera == getID());
}

void Camera::usePerspective(float fovDeg)
{
	const float NEAR = 0.1f;
	const float FAR = 1000.0f;

	m_mode = Modes::PERSPECTIVE;
	m_fovDeg = fovDeg;
	glm::vec2 viewportDim = m_parent->window()->getViewportSize();
	float fovRad = glm::radians(fovDeg);
	m_projMatrix = glm::perspectiveFov(fovRad, viewportDim.x, viewportDim.y, NEAR, FAR);
}

void Camera::use2D()
{
	m_projMatrix = glm::mat4{1.0f};
}

}
