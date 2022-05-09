#include "engine/ecs/components/transform.hpp"

#include "engine/ecs/component.hpp"

#include <iostream>

namespace engine {
namespace ecs {
namespace components {

Transform::Transform(ecs::Object* parent) : Component(parent)
{
	std::cerr << "Transform component " << getID() << " constructed\n";
}

Transform::~Transform()
{
	std::cerr << "Transform component " << getID() << " destroyed\n";
}

std::string Transform::getTypeName()
{
	return "transform";
}

}}}
