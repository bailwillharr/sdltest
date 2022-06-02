#include "components/camera.hpp"

#include "resources/shader.hpp"

static const std::string VIEW_MAT_UNIFORM = "viewMat";
static const std::string PROJ_MAT_UNIFORM = "projMat";

namespace components {

Camera::Camera(Object* parent) : Component(parent, "camera")
{

}

void Camera::onUpdate(glm::mat4 transform)
{

	using namespace resources;

	auto resPtrs = m_parent->resMan()->getAllResourcesOfType("shader");
	for (const auto& resPtr : resPtrs) {
		// shader ref count increased by 1, but only in this scope
		auto shader = dynamic_cast<Shader*>(resPtr.lock().get());
		if (shader->getUniformType(VIEW_MAT_UNIFORM) == Shader::UniformType::FLOAT_MAT4 &&
			shader->getUniformType(PROJ_MAT_UNIFORM) == Shader::UniformType::FLOAT_MAT4) {
			shader->setUniform(VIEW_MAT_UNIFORM, m_viewMatrix);
			shader->setUniform(PROJ_MAT_UNIFORM, m_projMatrix);
		}
	}
}

void Camera::onRender(glm::mat4 transform)
{

}

}
