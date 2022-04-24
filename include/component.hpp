#pragma once

#include <string>
#include <memory>

namespace component {

class Component {

private:
	static int s_component_count;

	int m_id;

public:
	Component();
	virtual ~Component() = 0;

	int getID();

	virtual std::string getName() = 0;

};

}
