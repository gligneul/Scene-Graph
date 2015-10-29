/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef TOONSHADER_H
#define TOONSHADER_H

#include <string>

#include "Appearance.h"

class ToonShader : public Appearance {
public:
    /**
     * Loads and compiles the shader
     */
    static void Init();

    /**
     * Creates a instance for the shader parameters
     */
    ToonShader();

    /**
     * Loads the appearance
     */
    void Load();

    /**
     * Unloads the appearance
     */
    void Unload();

private:
    /**
     * Reads the whole file and returns it as a string
     */
    static std::string ReadFile(const char *path);

    /**
     * Loads and compiles a shader from a file
     */
    static unsigned int LoadShader(int shader_type, const char *path);

    static unsigned int program_;
};

#endif

