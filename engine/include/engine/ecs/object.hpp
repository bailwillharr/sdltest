#pragma once

#include "engine/ecs/component.hpp"

#include "engine/ecs/components/transform.hpp"

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

namespace engine {
namespace ecs {

// Holds everything you would expect to find in a game scene
class Object {

private:
	static int s_object_count;
	int m_id = s_object_count;
	std::string m_name;
	std::list<std::shared_ptr<Object>> m_children{};
	std::list<std::shared_ptr<Component>> m_components{};

public:
	Object(std::string name);
	~Object();

	std::string getName();

	std::weak_ptr<Object> getChild(std::string name);
	std::vector<std::weak_ptr<Object>> getChildren();

	std::weak_ptr<Object> createChild(std::string name);
	void deleteChild(std::string name);

	void printTree(int level = 0);

	// Returns the component of type T
	// Returns nullptr if the component is not found.
	template<class T> std::weak_ptr<T> getComponent();

	// returns the component added
	template<class T> std::weak_ptr<T> createComponent();

	template<class T> void deleteComponent();

};

// implementation of template functions

template<class T> std::weak_ptr<T> Object::getComponent()
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("getComponent() error: specified type is not a subclass of 'Component'");
	}
	for (std::shared_ptr<Component>& component : m_components) {
		std::weak_ptr<T> derived = std::dynamic_pointer_cast<T>(component);
		if (derived.expired() == false) {
			return derived;
		}
	}
	return std::weak_ptr<T>();
}

template <class T> std::weak_ptr<T> Object::createComponent()
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("addComponent() error: specified type is not a subclass of 'Component'");
	}
	if (getComponent<T>().expired() == false) {
		throw std::runtime_error("addComponent() error: attempt to add component of a type already present");
	}
	m_components.emplace_back(new T(this));
	return std::dynamic_pointer_cast<T>(m_components.back());
}

template<class T> void Object::deleteComponent()
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("deleteComponent() error: specified type is not a subclass of 'Component'");
	}
	if (std::is_same<T, components::Transform>::value) {
		throw std::runtime_error("deleteComponent() error: attempt to remove the 'Transform' component");
	}
	for (std::list<std::shared_ptr<Component>>::iterator itr = m_components.begin(); itr != m_components.end(); ++itr) {
		if (std::dynamic_pointer_cast<T>(*itr)) {
			m_components.erase(itr);
			return;
		}
	}
	throw std::runtime_error("deleteComponent() error: attempt to delete component that is not present.");
}

}}
