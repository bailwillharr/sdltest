#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>

namespace engine {
namespace rendering {

enum class UniformType {
		FLOAT_MAT4 = GL_FLOAT_MAT4
};

struct Uniform {
		std::string name;
		GLint size;
		UniformType type;
};

class Shader {
private:

	// fields

	GLuint m_program;

	std::vector<Uniform> m_uniforms{};

public:
	Shader(std::string name);
	~Shader();

	const std::vector<Uniform>& getUniforms();

};

}}
