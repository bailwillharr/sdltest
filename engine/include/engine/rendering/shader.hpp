#pragma once

#include <glad/glad.h>

#include <glm/mat4x4.hpp>

#include <string>
#include <unordered_map>

namespace engine {
namespace rendering {

enum class UniformType {
		FLOAT_MAT4 = GL_FLOAT_MAT4
};

struct Uniform {
		GLint size;
		UniformType type;
		GLuint location;
};

class Shader {
private:

	// Only valid if glUseProgram is never called elsewhere
	static GLuint s_activeProgram;

	// fields

	GLuint m_program;

	std::unordered_map<std::string, Uniform> m_uniforms{};

	void makeActive();

public:
	Shader(std::string name);
	~Shader();

	bool setUniform(const std::string& name, const glm::mat4& m);

};

}}
