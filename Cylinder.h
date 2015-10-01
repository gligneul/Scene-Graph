/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class GLUquadric;

class Cylinder : public Shape {
public:
    /**
     * Constructor
     */
    Cylinder(float base = 1.0f, float top = 1.0f, float height = 1.0f,
            bool closed = true);

    /**
     * Destructor
     */
    ~Cylinder();

    /**
     * Set cube dimensions
     */
    void SetDimensions(float base, float top, float height);

    /**
     * Draws the shape
     */
    void Draw();

    /**
     * Set whether the cylinder is cloned or not
     */
    void SetClosed(bool closed);

private:
    float base_, top_, height_;
    bool closed_;
    GLUquadric* quadric_;
};

#endif

