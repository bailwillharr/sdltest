#include "components/camera.hpp"

#include "resources/shader.hpp"

static const std::string VIEW_MAT_UNIFORM = "viewMat";
static const std::string PROJ_MAT_UNIFORM = "projMat";

namespace components {

// -1 means no active camera
int Camera::s_activeCamera = -1;

Camera::Camera(Object* parent) : Component(parent, "camera")
{

}

void Camera::updateCam(glm::mat4 transform)
{

	(void)transform;

	using namespace resources;

	auto resPtrs = m_parent->resMan()->getAllResourcesOfType("shader");
	for (const auto& resPtr : resPtrs) {
		// shader ref count increased by 1, but only in this scope
		auto lockedPtr = resPtr.lock();
		auto shader = dynamic_cast<Shader*>(lockedPtr.get());
		if (shader->getUniformType(VIEW_MAT_UNIFORM) == Shader::UniformType::FLOAT_MAT4 &&
			shader->getUniformType(PROJ_MAT_UNIFORM) == Shader::UniformType::FLOAT_MAT4) {
			shader->setUniform(VIEW_MAT_UNIFORM, m_viewMatrix);
			shader->setUniform(PROJ_MAT_UNIFORM, m_projMatrix);
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);

}

void Camera::makeActive()
{
	s_activeCamera = getID();
}

}
