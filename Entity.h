/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

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
     * Sets the appearance
     */
    void SetAppearance(std::shared_ptr<Appearance> appearance);

    /**
     * Sets the shape
     */
    void SetShape(std::shared_ptr<Shape> shape);

    /**
     * Renders the entities
     */
    void Render();

private:
    std::shared_ptr<Appearance> appearance_;
    std::shared_ptr<Shape> shape_;
};

#endif

