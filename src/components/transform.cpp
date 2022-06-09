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

}
