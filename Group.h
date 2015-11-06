/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
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
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

    /**
     * Sets the lights
     * Returns the light info by reference
     */
    virtual void SetupLight(const glm::mat4& modelview, 
            std::vector<LightInfo>& lights);

    /**
     * Renders the node
     */
    virtual void Render(const std::vector<LightInfo>& lights,
            const glm::mat4& projection, const glm::mat4& modelview);

private:
    /** Group's children */
    std::vector<std::shared_ptr<Node>> nodes_;
};

#endif

