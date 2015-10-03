/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <vector>

#include "Node.h"

/**
 * A container for other nodes
 */
class Group : public Node {
public:
    /**
     * Virtual destructor
     */
    ~Group();

    /**
     * Adds a node to the group
     */
    void AddNode(std::shared_ptr<Node> node);

    /**
     * Sets the camera
     * Receives the reference to the output modelView
     * Returns true if the camera has been set
     */
    virtual bool SetupCamera(float* modelView);

    /**
     * Sets the lights
     * Receives the light id
     * Returns the next light id
     */
    virtual int SetupLight(int light_id);

    /**
     * Renders the entities
     */
    virtual void Render();

private:
    /** Group's children */
    std::vector<std::shared_ptr<Node>> nodes_;
};

#endif

