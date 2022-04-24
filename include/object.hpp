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

	// ensure that T inherits from 'Component'
	template<class T> std::shared_ptr<T> getComponent();

};



// implementation of template functions

template<class T> std::shared_ptr<T> Object::getComponent()
{
	if (std::is_base_of<component::Component, T>::value == false) {
		throw std::runtime_error("getComponent() error: specified type is not a subclass of 'Object'");
	}
	for (auto component : m_components) {
		if (std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(component)) {
			return derived;
		}
	}
	return nullptr;
}

}
