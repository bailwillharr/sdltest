#include "ecs/components/camera.hpp"

namespace engine {
namespace ecs {
namespace components {

Camera::Camera(engine::ecs::Object* parent) : Component(parent, "camera")
{
	
}

void Camera::onUpdate(glm::mat4 transform)
{
	 
}

void Camera::onRender(glm::mat4 transform)
{

}

}
}
}