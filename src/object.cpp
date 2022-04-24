#include "object.hpp"

#include "components/transform.hpp"
#include "components/camera.hpp"

#include <type_traits>
#include <stdexcept>

namespace object {

Object::Object(std::string name) : m_name(name)
{
	m_components.emplace_back(new component::Transform());
	m_components.emplace_back(new component::Camera());
}

Object::~Object()
{

}

std::list<std::shared_ptr<Object>> Object::getChildren()
{
	return m_children;
}



};
