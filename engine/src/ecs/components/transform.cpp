#include "engine/ecs/components/transform.hpp"

#include "engine/ecs/component.hpp"

#include <iostream>

namespace components {

Transform::Transform(ecs::Object* parent) : Component(parent)
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
