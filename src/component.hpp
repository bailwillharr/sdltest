#pragma once

#include <glm/mat4x4.hpp>

#include <string>
#include <memory>
#include <list>

class Object;

class Component {

public:

	enum class TypeEnum {
		TRANSFORM,
		CAMERA,
		RENDERER,
		CUSTOM,
	};

	Component(Object* parent, TypeEnum type);
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
	virtual ~Component() = 0;
	
	int getID();
	TypeEnum getType();

protected:
	Object* m_parent;

private:
	static int s_next_component_id;

	int m_id = s_next_component_id;
	TypeEnum m_type;

};
