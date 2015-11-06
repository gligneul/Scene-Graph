/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <GL/glew.h>

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& prefix) :
    program_(glCreateProgram()) {
    auto vs = LoadShader(GL_VERTEX_SHADER, prefix + "_vs.glsl"); 
    auto fs = LoadShader(GL_FRAGMENT_SHADER, prefix + "_fs.glsl");
    glAttachShader(program_, fs);
    glAttachShader(program_, vs);

    // TODO: verify link errors
    glLinkProgram(program_);
}

ShaderProgram::~ShaderProgram() {
    // TODO: destroy shader
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

unsigned int ShaderProgram::LoadShader(int shader_type,
        const std::string& path) {
    auto shader_str = ReadFile(path);
    auto shader_ptr = shader_str.c_str();
    auto shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_ptr, NULL);
    glCompileShader(shader);
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetShaderInfoLog(shader, length, &length, log);
        glDeleteShader(shader);
        std::cerr << "Error: " << log << "\n";
    }
    return shader;
}

