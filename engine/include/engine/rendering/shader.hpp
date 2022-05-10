#pragma once

#include <glad/glad.h>

#include <string>

namespace engine {
namespace rendering {

class Shader {
private:
	GLuint m_program;

public:
	Shader(std::string name);
	~Shader();
};

}}