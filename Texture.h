/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "Appearance.h"

class Texture : public Appearance {
public:
    /**
     * Constructor for an 2D texture
     * Receives the path to the texture file (png only)
     * Throws runtime_error if the file dimensions aren't base 2
     */
    Texture(const std::string& path);

    /**
     * Destructor
     */
    ~Texture();

    /**
     * Loads the appearance
     */
    void Load();

    /**
     * Unloads the appearance
     */
    void Unload();

private:
    unsigned int _id;
};

#endif

