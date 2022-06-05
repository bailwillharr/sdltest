#include "components/transform.hpp"

#include "component.hpp"

#include <iostream>

namespace components {

Transform::Transform(Object* parent) : Component(parent, TypeEnum::TRANSFORM)
{
}

Transform::~Transform()
{
}


void Transform::translate(glm::vec3 t)
{
	m_transformMatrix = glm::translate(m_transformMatrix, t);
}

void Transform::rotate(float radians, glm::vec3 t)
{
	m_transformMatrix = glm::rotate(m_transformMatrix, radians, t);
}

void Transform::scale(glm::vec3 factor)
{
	m_transformMatrix = glm::scale(m_transformMatrix, factor);
}

}
