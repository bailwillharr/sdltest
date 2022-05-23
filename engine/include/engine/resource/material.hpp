#pragma once

#include "engine/resource/resource.hpp"
#include "engine/rendering/shader.hpp"

namespace engine::resource {

class Material : public Resource, public engine::rendering::Shader {
private:
	
public:
	Material();
	~Material() = default;
};

}