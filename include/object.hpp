#pragma once

#include "component.hpp"

#include <list>
#include <string>
#include <memory>
#include <stdexcept>

namespace object {

// Holds everything you would expect to find in a game scene
class Object {

private:
	std::string m_name;
	std::list<std::shared_ptr<Object>> m_children;
	std::list<std::shared_ptr<component::Component>> m_components;

public:
	Object(std::string name);
	~Object();

	std::list<std::shared_ptr<Object>> getChildren();
	std::shared_ptr<Object> createChild(std::string name);

	void printTree(int level = 0);

	std::list<std::shared_ptr<component::Component>> getComponents();

	// Returns the component of type T that is attached to this objecs.
	// Returns nullptr if the component is not found.
	template<class T> std::shared_ptr<T> getComponent();

	// returns the component added
	template<class T> std::shared_ptr<T> createComponent();

};



// implementation of template functions

template<class T> std::shared_ptr<T> Object::getComponent()
{
	if (std::is_base_of<component::Component, T>::value == false) {
		throw std::runtime_error("getComponent() error: specified type is not a subclass of 'Component'");
	}
	for (auto component : m_components) {
		if (std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(component)) {
			return derived;
		}
	}
	return nullptr;
}

template <class T> std::shared_ptr<T> Object::createComponent()
{
	if (std::is_base_of<component::Component, T>::value == false) {
		throw std::runtime_error("addComponent() error: specified type is not a subclass of 'Component'");
	}
	if (getComponent<T>() != nullptr) {
		throw std::runtime_error("addComponent() error: attempt to add component of a type already present under object '" + m_name + "'");
	}
	m_components.emplace_back(new T());
	return std::dynamic_pointer_cast<T>(m_components.back());
}

}
