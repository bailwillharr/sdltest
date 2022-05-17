#include "engine/rendering/material.hpp"

#include <iostream>

namespace engine{
namespace rendering {

Material::Material() : Shader("texture")
{
	std::cout << "Hello world!\n";
}

Material::~Material()
{

}

}}
