#include "components/transform.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Transform::Transform(object::Object* parent) : Component(parent)
{
	std::cout << "Transform component " << getID() << " constructed\n";
}

Transform::~Transform()
{
	std::cout << "Transform component " << getID() << " destroyed\n";
}

std::string Transform::getTypeName()
{
	return "transform";
}

}
