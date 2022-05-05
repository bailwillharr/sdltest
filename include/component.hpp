#pragma once

#include <string>
#include <memory>
#include <list>

namespace object {
class Object;
}

namespace component {

class Component {

private:
	static int s_component_count;

	int m_id;

	object::Object* m_parent;

public:
	Component(object::Object* parent);
	virtual ~Component() = 0;
	
	int getID();
	virtual std::string getTypeName() = 0;

	// events
	virtual void onUpdate();
	virtual void onRender();

};

}
