#pragma once

#include <string>
#include <memory>

namespace component {

struct ComponentCacheBase {
	virtual ~ComponentCacheBase() = 0;
};

class Component {

private:
	static int s_component_count;

	int m_id;

public:
	Component();
	virtual ~Component() = 0;

	int getID();

	virtual std::string getTypeName() = 0;

	virtual std::shared_ptr<ComponentCacheBase> getCacheEntry() = 0;

};

}
