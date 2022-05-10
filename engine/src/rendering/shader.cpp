#include "engine/rendering/shader.hpp"

#include <glad/glad.h>

#include <string>

#include <iostream>

namespace engine{
namespace rendering {

static GLuint compile(const char *path, GLenum type)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        throw std::runtime_error("Error opening shader file: " + std::string(path));
    }

    // copy file into buffer
    fseek(fp, 0, SEEK_END);
    GLint len = (GLint)ftell(fp);
    char *src = (GLchar *)calloc(1, len + 1);
    if (src == NULL) {
        throw std::runtime_error("Error allocating memory for shader src");
    }
    fseek(fp, 0, SEEK_SET);
    fread(src, 1, len, fp);
    fclose(fp);

    // compile shader
    GLuint handle = glCreateShader(type);
    glShaderSource(handle, 1, (const GLchar **)&src, (const GLint *)&len);
    glCompileShader(handle);
    free(src);

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
    }

    return handle;
}

Shader::Shader(std::string name)
{
	std::string vertexShaderPath = "shaders/" + name + ".vert";
	std::string fragmentShaderPath = "shaders/" + name + ".frag";
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
            throw std::runtime_error("Error allocating memory for program linking error log");
        }
        glGetProgramInfoLog(m_program, log_len, NULL, log_msg);
        throw std::runtime_error("Program linking error with " + vertexShaderPath + " and " + fragmentShaderPath + " log:\n" + log_msg);
    }

}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

}}