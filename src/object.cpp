#include "object.hpp"

namespace object {

Object::Object(std::string name) : m_name(name)
{

}

Object::~Object()
{

}

std::vector<std::shared_ptr<Object>> Object::getChildren()
{
	return m_children;
}

template<class T> std::shared_ptr<T> Object::getComponent()
{
// TODO linear search to find first component with correct type
}

};
