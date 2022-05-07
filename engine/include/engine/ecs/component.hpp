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

	Object* m_parent;

public:
	Component(Object* parent);
	virtual ~Component() = 0;
	
	int getID();
	virtual std::string getTypeName() = 0;

	// events
	virtual void onUpdate();
	virtual void onRender();

};

}}
