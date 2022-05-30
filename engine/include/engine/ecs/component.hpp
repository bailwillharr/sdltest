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
	static int s_next_component_id;
	
	int m_id = s_next_component_id;
	std::string m_typeName;

protected:
	Object* m_parent;

public:
	Component(Object* parent, std::string typeName);
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
	virtual ~Component() = 0;
	
	int getID();

	// events
	virtual void onUpdate(glm::mat4 transform);
	virtual void onRender(glm::mat4 transform);

};

}}
