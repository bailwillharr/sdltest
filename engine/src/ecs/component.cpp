#include "engine/ecs/component.hpp"

#include <iostream>

namespace engine {
namespace ecs {

int Component::s_next_component_id = 0;

Component::Component(Object* parent, std::string typeName) : m_typeName(typeName), m_parent(parent)
{
	s_next_component_id++;
	std::cerr << "Component " << m_id << " of type " << m_typeName << " has been constructed\n";
}

Component::~Component()
{
	std::cerr << "Component " << m_id << " of type " << m_typeName << " has been destructed\n";
}

int Component::getID()
{
	return m_id;
}

void Component::onUpdate(glm::mat4 transform) { }

void Component::onRender(glm::mat4 transform) { }

}}
