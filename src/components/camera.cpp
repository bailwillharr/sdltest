#include "components/camera.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Camera::Camera()
{

}

Camera::~Camera()
{
}

std::string Camera::getTypeName()
{
	return "camera";
}

std::shared_ptr<ComponentCacheBase> Camera::getCacheEntry()
{
	return nullptr;
}

}
