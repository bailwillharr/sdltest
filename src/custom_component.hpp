#pragma once

#include "component.hpp"

#include <glm/mat4x4.hpp>

#include <string>

class CustomComponent : public Component {

public:
	CustomComponent(Object* parent);
	virtual ~CustomComponent() = 0;

	virtual void onInit() = 0;
	virtual void onUpdate() = 0;

};