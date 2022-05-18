#pragma once

#include <glad/glad.h>

#include <glm/mat4x4.hpp>

#include <string>
#include <map>

namespace engine {
namespace rendering {

enum class UniformType {
		FLOAT_MAT4 = GL_FLOAT_MAT4,
		FLOAT_VEC3 = GL_FLOAT_VEC3
};

struct Uniform {
		GLint size;
		UniformType type;
		GLuint location;
};

struct Attribute {
		GLint size;
		UniformType type;
		GLuint location;
};

class Shader {
private:

	// Only valid if glUseProgram is never called elsewhere
	static GLuint s_activeProgram;

	// fields

	std::map<std::string, Uniform> m_uniforms{};
	std::map<std::string, Attribute> m_attributes{};

	void makeActive();

public:
	Shader(std::string name);
	~Shader();

	GLuint m_program;

	bool setUniform(const std::string& name, const glm::mat4& m);
	bool setUniform(const std::string& name, const glm::vec3& v);

	int getAttribLocation(const std::string& name) const;

};

}}
