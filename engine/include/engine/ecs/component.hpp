#pragma once

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
	virtual void onUpdate();
	virtual void onRender();

};

}}
