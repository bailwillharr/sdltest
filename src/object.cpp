#include "object.hpp"

#include "components/transform.hpp"
#include "components/camera.hpp"
#include "components/renderer.hpp"
#include "components/custom.hpp"

#include <iostream>

int Object::s_object_count = 0;

Object::Object(std::string name, Object* parent, struct GameIO things)
	: m_name(name), m_parent(parent),
	m_gameIO(things),
	win(*things.win),
	inp(*things.input),
	res(*things.resMan)
{
	s_object_count++;
	// all objects come with at least a transform component
	createComponent<components::Transform>();
#ifndef NDEBUG
	std::cerr << "Object " << m_id << " '" << m_name << "' has been constructed\n";
#endif
}

Object::~Object()
{
#ifndef NDEBUG
	std::cerr << "Object " << m_id << " '" << m_name << "' has been destroyed\n";
#endif
}

std::string Object::getName()
{
	return m_name;
}

Object* Object::getParent()
{
	return m_parent;
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
	m_children.emplace_back(std::make_unique<Object>(name, this, m_gameIO));
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

void Object::printTree(int level)
{
	for (int i = 0; i < level; i++) {
		if (i+1 == level) {
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

void Object::getAllSubComponents(struct CompList& compList, glm::mat4 parentTransform)
{
	using namespace components;

	glm::mat4 objTransform{1.0f};

	auto t = getComponent<Transform>();

	// rotation
	objTransform = glm::mat4_cast(t->rotation);

	// position
	reinterpret_cast<glm::vec3&>(objTransform[3]) = t->position;
	
	// scale (effectively applied first
	objTransform = glm::scale(objTransform, t->scale);

	const glm::mat4 newTransform = parentTransform * objTransform;

	for (const auto& compUnq : m_components) {
		const auto comp = compUnq.get();
		switch (comp->getType()) {
		case Component::TypeEnum::CAMERA:
			compList.cameras.emplace_back(dynamic_cast<Camera*>(comp), newTransform);
			break;
		case Component::TypeEnum::RENDERER:
			compList.renderers.emplace_back(dynamic_cast<Renderer*>(comp), newTransform);
			break;
		case Component::TypeEnum::CUSTOM:
			compList.customs.emplace_back(dynamic_cast<CustomComponent*>(comp), newTransform);
			break;
		default:
			break;
		}
	}
	for (const auto& child : m_children) {
		child->getAllSubComponents(compList, newTransform);
	}
}
