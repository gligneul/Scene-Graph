/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& prefix) :
    program_(glCreateProgram()) {
    CompileShader(GL_VERTEX_SHADER, prefix + "_vs.glsl"); 
    CompileShader(GL_FRAGMENT_SHADER, prefix + "_fs.glsl");
    LinkShader();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program_);
}

unsigned int ShaderProgram::GetHandle() {
    return program_;
}

std::string ShaderProgram::ReadFile(const std::string& path) {
    std::ifstream input(path);
    if (!input.is_open())
        throw std::runtime_error("Unable to open file: " + path);
    std::string output;
    while (!input.eof()) {
        char line[1024];
        input.getline(line, 1024);
        output = output + line + "\n";
    }
    return output;
}

void ShaderProgram::Enable() {
    glUseProgram(program_);
}

void ShaderProgram::Disable() {
    glUseProgram(0);
}

void ShaderProgram::SetUniformInteger(const char *name, int value) {
    GLuint location = glGetUniformLocation(program_, name);
    glUniform1i(location, value);
}

void ShaderProgram::SetUniformFloat(const char *name, float value) {
    GLuint location = glGetUniformLocation(program_, name);
    glUniform1f(location, value);
}

void ShaderProgram::SetUniformVec3(const char *name, const glm::vec3& value) {
    GLuint location = glGetUniformLocation(program_, name);
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniformVec4(const char *name, const glm::vec4& value) {
    GLuint location = glGetUniformLocation(program_, name);
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniformMat4(const char *name, const glm::mat4& value) {
    GLuint location = glGetUniformLocation(program_, name);
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::SetAttribLocation(const char *name, unsigned int location) {
    glBindAttribLocation(program_, location, name);
}

void ShaderProgram::CompileShader(int shader_type, const std::string& path) {
    auto shader_str = ReadFile(path);
    auto shader_cstr = shader_str.c_str();
    auto shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_cstr, NULL);
    glCompileShader(shader);
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetShaderInfoLog(shader, length, &length, log);
        glDeleteShader(shader);
        throw std::runtime_error(log);
    }
    glAttachShader(program_, shader);
}

void ShaderProgram::LinkShader() {
    glLinkProgram(program_);
    // TODO verify status
}

