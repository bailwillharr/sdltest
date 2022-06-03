#include "component.hpp"

#include <iostream>

int Component::s_next_component_id = 0;

Component::Component(Object* parent, std::string typeName) : m_typeName(typeName), m_parent(parent)
{
	s_next_component_id++;
#ifdef SDLTEST_DEBUG
	std::cerr << "Component " << m_id << " of type " << m_typeName << " has been constructed\n";
#endif
}

Component::~Component()
{
#ifdef SDLTEST_DEBUG
	std::cerr << "Component " << m_id << " of type " << m_typeName << " has been destructed\n";
#endif
}

int Component::getID()
{
	return m_id;
}
