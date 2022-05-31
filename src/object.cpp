#include "object.hpp"

#include "components/transform.hpp"

#include <vector>
#include <memory>
#include <type_traits>
#include <stdexcept>
#include <iostream>

int Object::s_object_count = 0;

Object::Object(std::string name) : m_name(name)
{
	s_object_count++;
	// all objects come with at least a transform component
	createComponent<components::Transform>();
	std::cerr << "Object " << m_id << " '" << m_name << "' has been constructed\n";
}

Object::~Object()
{
	std::cerr << "Object " << m_id << " '" << m_name << "' has been destroyed\n";
}

std::string Object::getName()
{
	return m_name;
}

Object* Object::getChild(std::string name)
{
	for (const auto& child : m_children) {
		if (name == child->getName()) {
			return child.get();
		}
	}
	return nullptr;
}

std::vector<Object*> Object::getChildren()
{
	std::vector<Object*> newVector{};
	for (const auto& child : m_children) {
		newVector.push_back(child.get());
	}
	return newVector;
}

Object* Object::createChild(std::string name)
{
	if (getChild(name) != nullptr) {
		throw std::runtime_error("Attempt to create child object with existing name");
	}
	m_children.emplace_back(std::make_unique<Object>(name));
	return m_children.back().get();
}

void Object::deleteChild(std::string name)
{
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr) {
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
			//std::cerr << "└4───────";
			std::cerr << "\\_______";
		} else {
			std::cerr << "        ";
		}
	}
	std::cerr << m_name << "\n";
	for (const auto& child : this->getChildren()) {
		child->printTree(level+1);
	}
}

void Object::updateComponents(glm::mat4 transform)
{
	for (const auto& comp : m_components) {
		comp->onUpdate(transform);
	}
}

void Object::renderComponents(glm::mat4 transform)
{
	for (const auto& comp : m_components) {
		comp->onRender(transform);
	}
}

void Object::updateObjectAndChildren(glm::mat4 parentTransform)
{
	glm::mat4 newTransform;
	const auto transform = getComponent<components::Transform>();
	newTransform = parentTransform * transform->m_transformMatrix;

	updateComponents(newTransform);

	for (const auto& obj : m_children) {
		obj->updateObjectAndChildren(newTransform);
	}
}

void Object::renderObjectAndChildren(glm::mat4 parentTransform)
{
	glm::mat4 newTransform;
	const auto transform = getComponent<components::Transform>();
	newTransform = parentTransform * transform->m_transformMatrix;

	renderComponents(newTransform);

	for (const auto& obj : m_children) {
		obj->renderObjectAndChildren(newTransform);
	}

}
