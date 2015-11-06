/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

class ShaderProgram {
public:
    /**
     * Loads, compiles and links the shader program
     * Expects a prefix (%) for the files: %_vs.glsl and %_fs.glsl
     */
    ShaderProgram(const std::string& prefix);

    /**
     * Destructor
     */
    ~ShaderProgram();

    /**
     * Obtains the shader program handle
     */
    unsigned int GetHandle();

private:
    /**
     * Reads the whole file and returns it as a string
     */
    std::string ReadFile(const std::string& path);

    /**
     * Loads and compiles a shader from a file
     */
    unsigned int LoadShader(int shader_type, const std::string& path);

    unsigned int program_;
};

#endif

