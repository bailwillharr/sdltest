#include "component.hpp"

#include <iostream>

namespace component {

int Component::s_component_count = 0;

Component::Component()
{
	m_id = s_component_count;
	s_component_count++;
}

Component::~Component() { }

int Component::getID()
{
	return m_id;
}

};
