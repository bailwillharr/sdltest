#pragma once

#include <string>
#include <memory>
#include <list>

namespace component {

class ComponentList;

class Component {

private:
	static int s_component_count;

	int m_id;

	std::shared_ptr<ComponentList> m_objectComponents;

public:
	Component(std::shared_ptr<ComponentList> compList);
	virtual ~Component() = 0;
	
	int getID();

	

	virtual std::string getTypeName() = 0;

	// events
	virtual void onUpdate();
	virtual void onRender();

};

}
