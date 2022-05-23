#include "engine/resource/material.hpp"

#include <iostream>

namespace engine::resource {

Material::Material() : Shader("texture"), Resource("name")
{
}

}