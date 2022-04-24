#include "object.hpp"

#include "components/transform.hpp"
#include "components/camera.hpp"

#include <type_traits>
#include <stdexcept>
#include <iostream>

namespace object {

Object::Object(std::string name) : m_name(name)
{
	// all objects come with at least a transform component
	m_components.emplace_back(new component::Transform());
	std::cout << "Object " << name << " has been constructed\n";
}

Object::~Object()
{
	std::cout << "Object class destructor: " << m_name << "\n";
}

std::list<std::shared_ptr<Object>> Object::getChildren()
{
	return m_children;
}


std::shared_ptr<Object> Object::createChild(std::string name)
{
	m_children.emplace_back(new Object(name));
	return m_children.back();
}

void Object::printTree(int level)
{
	for (int i = 0; i < level; i++) {
		std::cout << "\t";
	}
	std::cout << m_name << "\n";
	for (auto child : this->getChildren()) {
		child->printTree(level+1);
	}
}

};
