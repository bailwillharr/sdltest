#pragma once

#include "component.hpp"

#include <vector>
#include <string>
#include <memory>

namespace object {

// Holds everything you would expect to find in a game scene
class Object {

private:
	std::string m_name;
	std::vector<std::shared_ptr<Object>> m_children;

public:
	Object(std::string name);
	~Object();

	std::vector<std::shared_ptr<Object>> getChildren();

	// ensure that T inherits from 'Component'
	template<class T> std::shared_ptr<T> getComponent();

};

}
