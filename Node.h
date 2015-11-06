/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef NODE_H
#define NODE_H

#include <vector>

#include <glm/glm.hpp>

/**
 * A generic node that can be attached to the graph
 * It offers an empty implementation to it's methods
 */
class Node {
public:

    /**
     * Holds the light information
     */
    struct LightInfo {
        glm::vec4 position;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 ambient;
        bool is_spot;
        glm::vec3 direction;
        float cutoff;
        float exponent;
    };

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

