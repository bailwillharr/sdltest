#pragma once

#include "component.hpp"

#include <list>
#include <string>
#include <memory>
#include <stdexcept>

namespace component {

class ComponentList {

private:
	std::list<std::shared_ptr<Component>> m_components;

public:

	// Returns the component of type T
	// Returns nullptr if the component is not found.
	template<class T> std::unique_ptr<T> getComponent();

	// returns the component added
	template<class T> std::unique_ptr<T>& createComponent(std::unique_ptr<T> comp);

};



// implementation of template functions

template<class T> std::unique_ptr<T> ComponentList::getComponent()
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("getComponent() error: specified type is not a subclass of 'Component'");
	}
	printf("test 1\n");
	for (std::shared_ptr<Component> component : m_components) {
		if (std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(component)) {
			return derived;
		}
	}
	printf("test 2\n");
	return nullptr;
}

template <class T> std::unique_ptr<T>& ComponentList::createComponent(std::unique_ptr<T> comp)
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("addComponent() error: specified type is not a subclass of 'Component'");
	}
	if (getComponent<T>() != nullptr) {
		throw std::runtime_error("addComponent() error: attempt to add component of a type already present");
	}
	m_components.emplace_back(comp);
	return std::dynamic_pointer_cast<T>(m_components.back());
}

}
