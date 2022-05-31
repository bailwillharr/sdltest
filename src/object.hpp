#pragma once

#include "component.hpp"
#include "components/transform.hpp"

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

// This object lives until it is deleted by its parent(s) or finally when the "Scene" is destroyed.
// Therefore it is safe to return raw pointers
class Object {

private:
	static int s_object_count;
	int m_id = s_object_count;
	std::string m_name;
	std::list<std::unique_ptr<Object>> m_children{};
	std::list<std::unique_ptr<Component>> m_components{};

public:
	Object(std::string name);
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
	~Object();

	std::string getName();

	Object* getChild(std::string name);
	std::vector<Object*> getChildren();

	Object* createChild(std::string name);
	void deleteChild(std::string name);

	void printTree(int level = 0);

	// Returns the component of type T
	// Returns nullptr if the component is not found.
	template<class T> T* getComponent();

	// returns the component added
	template<class T> T* createComponent();

	template<class T> void deleteComponent();

	void updateComponents(glm::mat4 transform);
	void renderComponents(glm::mat4 transform);

	void updateObjectAndChildren(glm::mat4 transform);
	void renderObjectAndChildren(glm::mat4 transform);

};

// implementation of template functions

template<class T> T* Object::getComponent()
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("getComponent() error: specified type is not a subclass of 'Component'");
	}
	for (const auto& component : m_components) {
		T* derived = dynamic_cast<T*>(component.get());
		if (derived != nullptr) {
			return derived;
		}
	}
	return nullptr;
}

template <class T> T* Object::createComponent()
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("addComponent() error: specified type is not a subclass of 'Component'");
	}
	if (getComponent<T>() != nullptr) {
		throw std::runtime_error("addComponent() error: attempt to add component of a type already present");
	}
	m_components.emplace_back(std::make_unique<T>(this));
	return dynamic_cast<T*>(m_components.back().get());
}

template<class T> void Object::deleteComponent()
{
	if (std::is_base_of<Component, T>::value == false) {
		throw std::runtime_error("deleteComponent() error: specified type is not a subclass of 'Component'");
	}
	if (std::is_same<T, components::Transform>::value) {
		throw std::runtime_error("deleteComponent() error: attempt to remove the 'Transform' component");
	}
	for (auto itr = m_components.begin(); itr != m_components.end(); ++itr) {
		if (dynamic_cast<T*>((*itr).get()) != nullptr) {
			m_components.erase(itr);
			return;
		}
	}
	throw std::runtime_error("deleteComponent() error: attempt to delete component that is not present.");
}
