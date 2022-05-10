#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>

namespace engine {
namespace rendering {

class Shader {
private:

	// types: structs, enums etc

	enum class UniformType {
		FLOAT_MAT4 = GL_FLOAT_MAT4
	};

	struct Uniform {
		std::string name;
		GLint size;
		UniformType type;
	};

	// fields

	GLuint m_program;

	std::vector<Uniform> m_uniforms{};

public:
	Shader(std::string name);
	~Shader();
};

}}
