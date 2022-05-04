#include "object.hpp"

//#include "components/transform.hpp"
//#include "components/camera.hpp"

#include <memory>
#include <type_traits>
#include <stdexcept>
#include <iostream>

namespace object {

Object::Object(std::string name) : m_name(name)
{
	// all objects come with at least a transform component
	//m_componentList->createComponent<component::Transform>(std::unique_ptr<component::Transform>(new component::Transform(m_componentList)));
	std::cout << "Object '" << name << "' has been constructed\n";
}

Object::~Object()
{
	std::cout << "Object class destructor: '" << m_name << "'\n";
}

std::string Object::getName()
{
	return m_name;
}

std::weak_ptr<Object> Object::getChild(std::string name)
{
	for (std::shared_ptr<Object>& obj : m_children) {
		if (name == obj->getName()) {
			return obj; // copy the shared_ptr, increasing ref-count by 1
		}
	}
	return std::weak_ptr<Object>();
}

/*

std::unique_ptr<Object>& Object::createChild(std::string name)
{
	m_children.emplace_back(new Object(name));
	return m_children.back();
}

std::shared_ptr<component::ComponentList> Object::getCompList()
{
	return m_componentList;
}

void Object::printTree(int level)
{
	for (int i = 0; i < level; i++) {
		std::cout << "\t";
	}
	std::cout << m_name << "\n";
	for (auto& child : this->getChildren()) {
		child->printTree(level+1);
	}
}
*/

};
