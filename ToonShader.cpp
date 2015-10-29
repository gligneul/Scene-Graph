/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <fstream>
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
}

void ToonShader::Unload() {
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
    return shader;
}

