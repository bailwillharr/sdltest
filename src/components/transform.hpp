#pragma once

#include "component.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_float.hpp>

#include <vector>
#include <string>
#include <memory>

namespace components {

class Transform : public Component {

private:

public:
	Transform(Object*);
	~Transform() override;

	glm::mat4 m_transformMatrix{1.0f};

	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getRotation();

	void translate(glm::vec3 t);
	void rotate(float radians, glm::vec3 t);
	void scale(glm::vec3 factor);

};

}
