#include "component.hpp"

#include <iostream>

int Component::s_next_component_id = 0;

Component::Component(Object* parent, TypeEnum type) : m_type(type), m_parent(parent)
{
	s_next_component_id++;
}

Component::~Component()
{
}

int Component::getID()
{
	return m_id;
}

Component::TypeEnum Component::getType()
{
	return m_type;
}