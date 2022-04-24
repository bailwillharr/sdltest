#include "components/transform.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Transform::Transform()
{

}

Transform::~Transform()
{
}

std::string Transform::getTypeName()
{
	return "transform";
}

}
