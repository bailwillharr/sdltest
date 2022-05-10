#pragma once

#include "engine/ecs/component.hpp"

#include <vector>
#include <string>
#include <memory>

namespace engine {
namespace ecs {
namespace components {

class Renderer : public ecs::Component {

private:


public:
	Renderer(ecs::Object*);
	~Renderer() override;
	
};

}}}
