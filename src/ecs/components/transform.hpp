#pragma once

#include "ecs/component.hpp"

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

public:
	Transform(ecs::Object*);
	~Transform() override;

	glm::mat4 m_transformMatrix{1.0f};

	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getRotation();

	void translate(glm::vec3 t);
	void rotate(float radians, glm::vec3 t);


};

}}}
