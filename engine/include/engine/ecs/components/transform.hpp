#pragma once

#include "engine/ecs/component.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_float.hpp>

#include <vector>
#include <string>
#include <memory>

namespace engine {
namespace ecs {
namespace components {

class Transform : public ecs::Component {

private:
	glm::mat4 m_modelMatrix{1.0f};

public:
	Transform(ecs::Object*);
	~Transform() override;

	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getRotation();

};

}}}
