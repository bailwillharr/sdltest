#include "components/camera.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Camera::Camera(std::shared_ptr<ComponentList> compList) : Component(compList)
{

}

Camera::~Camera()
{
}

std::string Camera::getTypeName()
{
	return "camera";
}

}
