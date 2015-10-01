/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef SHAPE_H
#define SHAPE_H

/**
 * Abstract class for drawing shapes
 */
class Shape {
public:
    /**
     * Virtual destructor
     */
    virtual ~Shape() {}

    /**
     * Draws the shape
     */
    virtual void Draw() = 0;
};

#endif

