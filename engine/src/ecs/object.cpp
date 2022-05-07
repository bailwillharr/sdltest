#include "engine/ecs/object.hpp"

#include "engine/ecs/components/transform.hpp"

#include <vector>
#include <memory>
#include <type_traits>
#include <stdexcept>
#include <iostream>

namespace engine {
namespace ecs {

int Object::s_object_count = 0;

Object::Object(std::string name) : m_name(name)
{
	s_object_count++;
	// all objects come with at least a transform component
	createComponent<components::Transform>();
	std::cout << "Object " << m_id << " '" << m_name << "' has been constructed\n";
}

Object::~Object()
{
	std::cout << "Object " << m_id << " '" << m_name << "' has been destroyed\n";
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
	if (getChild(name).expired() == false) {
		throw std::runtime_error("Attempt to create child object with existing name");
	}
	m_children.emplace_back(std::make_shared<Object>(name));
	return m_children.back();
}

void Object::deleteChild(std::string name)
{
	for (std::list<std::shared_ptr<Object>>::iterator itr = m_children.begin();
		 itr != m_children.end(); ++itr) {
		if ((*itr)->getName() == name) {
			m_children.erase(itr);
			return;
		}
	}
	throw std::runtime_error("Unable to delete child '" + name + "' as it does not exist");
}

// TODO: improve this
void Object::printTree(int level)
{
	for (int i = 0; i < level; i++) {
		if (i+1 == level) {
			std::cout << "└───────";
		} else {
			std::cout << "        ";
		}
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

}}
