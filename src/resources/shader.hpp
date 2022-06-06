#pragma once

#include "resource.hpp"

#include <glad/glad.h>

#include <glm/mat4x4.hpp>

#include <string>
#include <map>

namespace resources {

class Shader : public Resource {

public:
	Shader(const std::filesystem::path& resPath);
	~Shader() override;

	enum class UniformType {
		FLOAT_MAT4 = GL_FLOAT_MAT4,
		FLOAT_VEC3 = GL_FLOAT_VEC3,
		SAMPLER_2D = GL_SAMPLER_2D,
		NOTFOUND
	};
	
	void makeActive() const;

	bool setUniform(const std::string& name, const glm::mat4& m) const;
	bool setUniform(const std::string& name, const glm::vec3& v) const;

	UniformType getUniformType(const std::string& name) const;
	int getAttribLocation(const std::string& name) const;

private:
	
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

	// fields

	GLuint m_program;

	std::map<std::string, Uniform> m_uniforms{};
	std::map<std::string, Attribute> m_attributes{};

	// static members
	
	// Only valid if glUseProgram is never called outside this class's method
	static GLuint s_activeProgram;

};

}
