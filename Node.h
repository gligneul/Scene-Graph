/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef NODE_H
#define NODE_H

/**
 * A generic node that can be attached to the graph
 * It offers an empty implementation to it's methods
 */
class Node {
public:
    /**
     * Constructor
     */
    Node();

    /**
     * Virtual destructor
     */
    virtual ~Node();

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

    /**
     * Sets whether the node is active
     */
    void SetActive(bool active);

    /**
     * Gets whether the node is active
     */
    bool GetActive();

protected:
    bool active_;
};

#endif

