#pragma once

#include "component.hpp"

#include <glm/mat4x4.hpp>

namespace components {

class UI : public Component {

private:

public:
	UI(Object*);
	~UI() override;

	// called every frame, do not call manually
	void render(glm::mat4 transform);

};

}
