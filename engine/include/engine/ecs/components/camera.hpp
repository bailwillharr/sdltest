#pragma once

#include "engine/ecs/component.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace engine {
namespace ecs {
namespace components {

class Camera : public Component {

private:
	glm::mat4 viewMatrix{ 1.0f };
	glm::mat4 projMatrix{ 1.0f };

public:
	Camera(engine::ecs::Object* parent);
	void onUpdate(glm::mat4 transform) override;
	void onRender(glm::mat4 transform) override;
};

}
}
}