#include "resources/shader.hpp"

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <span>

static std::unique_ptr<std::vector<char>> readFile(const char * path)
{
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	//file.exceptions(std::ifstream::failbit); // throw exception if file cannot be opened
	if (file.fail()) {
		throw std::runtime_error("Failed to open file for reading: " + std::string(path));
	}
	size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	auto buf = std::make_unique<std::vector<char>>();
	buf->resize(size);
	file.rdbuf()->sgetn(buf->data(), size);
	return buf;
}

static GLuint compile(const char *path, GLenum type)
{
	auto src = readFile(path);

    // compile shader
    GLuint handle = glCreateShader(type);
	GLint size = src->size();
	GLchar *data = src->data();
    glShaderSource(handle, 1, &data, &size);
    glCompileShader(handle);

    // check for compilation error
    GLint compiled;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
    if (compiled == 0) {
        GLint log_len;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_len);
        GLchar *log_msg = (GLchar *)calloc(1, log_len);
        if (log_msg == NULL) {
            throw std::runtime_error("Error allocating memory for shader compilation error log");
        }
        glGetShaderInfoLog(handle, log_len, NULL, log_msg);
        throw std::runtime_error("Shader compilation error in " + std::string(path) + " log:\n" + std::string(log_msg));
    } return handle;
}

namespace resources {

// I've got to do this because of GL's stupid state machine
GLuint Shader::s_activeProgram = 0;

Shader::Shader(const std::filesystem::path& resPath) : Resource(resPath, "shader")
{

	const std::string vertexShaderPath = (resPath.parent_path()/std::filesystem::path(resPath.stem().string() + ".vert")).string();
	const std::string fragmentShaderPath = (resPath.parent_path()/std::filesystem::path(resPath.stem().string() + ".frag")).string();
	GLuint vs = compile(vertexShaderPath.c_str(), GL_VERTEX_SHADER);
	GLuint fs = compile(fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
	m_program = glCreateProgram();
	glAttachShader(m_program, vs);	
	glAttachShader(m_program, fs);
	glLinkProgram(m_program);
	glValidateProgram(m_program);

	// flag shader objects for deletion, this does not take effect until the program is deleted
    glDeleteShader(vs);
    glDeleteShader(fs);

	GLint linked, validated;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
    glGetProgramiv(m_program, GL_VALIDATE_STATUS, &validated);
    if (linked == 0 || validated == 0) {
        GLint log_len;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &log_len);
        GLchar *log_msg = (GLchar *)calloc(1, log_len);
        if (log_msg == NULL) {
            throw std::runtime_error("Error allocating memory for shader linking error log");
        }
        glGetProgramInfoLog(m_program, log_len, NULL, log_msg);
        throw std::runtime_error("Program linking error with " + vertexShaderPath + " and " + fragmentShaderPath + " log:\n" + log_msg);
    }

	// now get uniforms
	GLint count;
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &count);
	for (int i = 0; i < count; i++) {
		char nameBuf[64] = {};
		GLint size;
		GLenum type;
		glGetActiveUniform(m_program, i, 63, NULL, &size, &type, nameBuf);
		m_uniforms[nameBuf] = Uniform{size, static_cast<UniformType>(type), (GLuint)i};
	}

	// now get all attributes
	glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &count);
	for (int i = 0; i < count; i++) {
		char nameBuf[64] = {};
		GLint size;
		GLenum type;
		glGetActiveAttrib(m_program, i, 63, NULL, &size, &type, nameBuf);
		m_attributes[nameBuf] = Attribute{size, static_cast<UniformType>(type), (GLuint)i};
#ifdef SDLTEST_DEBUG
        std::cerr << "Attrib " << nameBuf << " index: " << i << "\n";
#endif
	}

}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::makeActive() const
{
	if (s_activeProgram != m_program) {
#ifdef SDLTEST_DEBUG
        std::cerr << "Shader used\n";
#endif
		glUseProgram(m_program);
        s_activeProgram = m_program;
	}
}

bool Shader::setUniform(const std::string& name, const glm::mat4& m) const
{
	makeActive();
	Uniform u = m_uniforms.at(name);
	glUniformMatrix4fv(u.location, 1, GL_FALSE, &m[0][0]);
	return true;
}

bool Shader::setUniform(const std::string& name, const glm::vec3& v) const
{
	makeActive();
	Uniform u = m_uniforms.at(name);
	glUniform3f(u.location, v.x, v.y, v.z);
	return true;
}


Shader::UniformType Shader::getUniformType(const std::string& name) const
{
	try {
		Uniform u = m_uniforms.at(name);
		return u.type;
	} catch (const std::out_of_range& e) {
		return UniformType::NOTFOUND;
	}
}

int Shader::getAttribLocation(const std::string& name) const
{
	return m_attributes.at(name).location;
}

}
