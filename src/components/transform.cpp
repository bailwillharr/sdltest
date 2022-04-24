#include "components/transform.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Transform::Transform()
{

}

Transform::~Transform()
{
	std::cout << "Transform component destructor\n";
}

std::string Transform::getName()
{
	return "transform";
}

}
