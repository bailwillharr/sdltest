#include "components/renderer.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Renderer::Renderer(std::shared_ptr<ComponentList> compList) : Component(compList)
{

}

Renderer::~Renderer()
{

}

std::string Renderer::getTypeName()
{
	return "renderer";
}

}
