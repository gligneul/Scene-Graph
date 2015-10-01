/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "Node.h"

class Appearance;
class Shape;

/**
 * Represents an entity with appearance and shape
 */
class Entity : public Node {
public:
    /**
     * Constructor
     */
    Entity();

    /**
     * Destructor
     */
    ~Entity();

    /**
     * Sets the appearance
     */
    void SetAppearance(Appearance* appearance);

    /**
     * Sets the shape
     */
    void SetShape(Shape* shape);

    /**
     * Renders the entities
     */
    void Render();

private:
    Appearance* appearance_;
    Shape* shape_;
};

#endif

