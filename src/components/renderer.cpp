#include "components/renderer.hpp"

#include "component.hpp"

#include <iostream>

namespace component {

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

std::string Renderer::getTypeName()
{
	return "renderer";
}

std::shared_ptr<ComponentCacheBase> Renderer::getCacheEntry()
{
	return nullptr;
}

}
