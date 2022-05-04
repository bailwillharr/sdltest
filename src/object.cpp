#include "object.hpp"

//#include "components/transform.hpp"
//#include "components/camera.hpp"

#include <vector>
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
	for (std::shared_ptr<Object>& child : m_children) {
		if (name == child->getName()) {
			return child; // copy the shared_ptr, increasing ref-count by 1
		}
	}
	return std::weak_ptr<Object>();
}

std::vector<std::weak_ptr<Object>> Object::getChildren()
{
	std::vector<std::weak_ptr<Object>> weakVector{};
	for (std::shared_ptr<Object>& child : m_children) {
		weakVector.emplace_back(child);
	}
	return weakVector;
}

std::weak_ptr<Object> Object::createChild(std::string name)
{
	m_children.emplace_back(std::make_shared<Object>(name));
	return m_children.back();
}

void Object::printTree(int level)
{
	for (int i = 0; i < level; i++) {
		std::cout << "\t";
	}
	std::cout << m_name << "\n";
	for (std::weak_ptr<Object> childWP : this->getChildren()) {
		if (auto child = childWP.lock()) {
			child->printTree(level+1);
		} else {
			throw std::runtime_error("Unable to get lock on object pointer.");
		}
	}
}

/*
std::shared_ptr<component::ComponentList> Object::getCompList()
{
	return m_componentList;
}
*/

};
