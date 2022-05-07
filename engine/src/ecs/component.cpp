#include "engine/ecs/component.hpp"

#include <iostream>

namespace engine {
namespace ecs {

int Component::s_component_count = 0;

Component::Component(Object* parent) : m_parent(parent)
{
	s_component_count++;
	printf("Component %d has been constructed\n", m_id);
}

Component::~Component()
{
	printf("Component %d has been destructed\n", m_id);
}

int Component::getID()
{
	return m_id;
}

void Component::onUpdate() { }

void Component::onRender() { }

}}
