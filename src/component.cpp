#include "component.hpp"

#include <iostream>

namespace component {

int Component::s_component_count = 0;

Component::Component(std::shared_ptr<ComponentList> compList) : m_objectComponents(compList)
{
	m_id = s_component_count;
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

};
