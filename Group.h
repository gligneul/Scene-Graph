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
     * Sets the shadow map
     */
    virtual bool SetupShadowMap(ShadowMapInfo& info);

    /**
     * Renders the shadow map
     */
    virtual void RenderShadowMap(ShadowMapInfo& info,
            const glm::mat4& modelview);

    /**
     * Renders the node
     */
    virtual void Render(RenderInfo& info, const glm::mat4& modelview);

private:
    /** Group's children */
    std::vector<std::shared_ptr<Node>> nodes_;
};

#endif

