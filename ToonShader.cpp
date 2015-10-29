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

#include "ToonShader.h"

unsigned int ToonShader::program_ = 0;

void ToonShader::Init() {
    auto vs = LoadShader(GL_VERTEX_SHADER, "toonshader_vs.glsl"); 
    auto fs = LoadShader(GL_FRAGMENT_SHADER, "toonshader_fs.glsl");
    program_ = glCreateProgram();
    glAttachShader(program_, fs);
    glAttachShader(program_, vs);
    glLinkProgram(program_);
}

ToonShader::ToonShader() {
}

void ToonShader::Load() {
    glUseProgram(program_);

    float modelview[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
    GLuint modelview_location = glGetUniformLocation(program_, "modelview");
    glUniformMatrix4fv(modelview_location, 1, GL_FALSE, modelview);

    float projection[16];
    glGetFloatv(GL_PROJECTION_MATRIX, projection);
    GLuint projection_location = glGetUniformLocation(program_, "projection");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection);

    float color[3] = {0.5, 0, 0.5};
    GLuint color_location = glGetUniformLocation(program_, "color");
    glUniform3fv(color_location, 1, color);
}

void ToonShader::Unload() {
    glUseProgram(0);
}

std::string ToonShader::ReadFile(const char *path) {
    std::ifstream input(path);
    if (!input.is_open())
        throw std::runtime_error(std::string( "Unable to open file" ) + path);
    std::string output;
    while (!input.eof()) {
        char line[1024];
        input.getline(line, 1024);
        output = output + line + "\n";
    }
    return output;
}

unsigned int ToonShader::LoadShader(int shader_type, const char *path) {
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

