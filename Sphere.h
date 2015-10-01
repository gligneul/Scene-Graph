/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
    /**
     * Default constructor
     */
    Sphere(float radius = 1.0f);

    /**
     * Draws the shape
     */
    void Draw();

private:
    float radius_;
};

#endif

