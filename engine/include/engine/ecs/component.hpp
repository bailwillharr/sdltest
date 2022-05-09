#pragma once

#include <glm/mat4x4.hpp>

#include <string>
#include <memory>
#include <list>

namespace engine {
namespace ecs {

class Object;

class Component {

private:
	static int s_component_count;

	int m_id = s_component_count;
	std::string m_typeName;

	Object* m_parent;

public:
	Component(Object* parent, std::string typeName);
	virtual ~Component() = 0;
	
	int getID();

	// events
	virtual void onUpdate(glm::mat4 transform);
	virtual void onRender(glm::mat4 transform);

};

}}
