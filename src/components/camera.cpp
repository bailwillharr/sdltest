#include "components/camera.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Camera::Camera()
{

}

Camera::~Camera()
{
	std::cout << "Camera component destructor\n";
}

std::string Camera::getName()
{
	return "camera";
}

}
