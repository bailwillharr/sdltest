#pragma once

#include "resource.hpp"

#include <glad/glad.h>

#include <glm/mat4x4.hpp>

#include <string>
#include <map>

namespace resources {

class Shader : public Resource {
private:
	
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


	// Only valid if glUseProgram is never called elsewhere
	static GLuint s_activeProgram;

	// fields

	GLuint m_program;

	std::map<std::string, Uniform> m_uniforms{};
	std::map<std::string, Attribute> m_attributes{};

public:
	Shader(const std::filesystem::path& resPath);
	~Shader();
	
	void makeActive();

	bool setUniform(const std::string& name, const glm::mat4& m);
	bool setUniform(const std::string& name, const glm::vec3& v);

	int getAttribLocation(const std::string& name) const;

};

}
