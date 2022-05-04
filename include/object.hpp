#pragma once

//#include "component.hpp"

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

namespace object {

// Holds everything you would expect to find in a game scene
class Object {

private:
	std::string m_name;
	std::list<std::shared_ptr<Object>> m_children{};
	//std::shared_ptr<component::ComponentList> m_componentList{new component::ComponentList};

public:
	Object(std::string name);
	~Object();

	std::string getName();

	std::weak_ptr<Object> getChild(std::string name);
	std::vector<std::weak_ptr<Object>> getChildren();
	std::weak_ptr<Object> createChild(std::string name);

	//std::shared_ptr<component::ComponentList> getCompList();

	void printTree(int level = 0);

};

}
