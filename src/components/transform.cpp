#include "components/transform.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Transform::Transform(std::shared_ptr<ComponentList> compList) : Component(compList)
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
