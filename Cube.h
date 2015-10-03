/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

/**
 * Unitary cube centered in 0, 0, 0
 */
class Cube : public Shape {
public:
    /**
     * Constructor
     * Receives the cube dimensions
     */
    Cube(float dx = 1.0f, float dy = 1.0f, float dz = 1.0f);

    /**
     * Set cube dimensions
     */
    void SetDimensions(float dx, float dy, float dz);

    /**
     * Draws the shape
     */
    void Draw();

private:
    float dx_, dy_, dz_;
};

#endif

