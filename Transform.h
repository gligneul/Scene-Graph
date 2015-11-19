/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <memory>

#include "Group.h"

class Manipulator;

class Transform : public Group {
public:
    /**
     * Constructor
     * Loads the identity by default
     */
    Transform();

    /**
     * Loads the identity matrix
     */
    void LoadIndentity();

    /**
     * Multiply the current matrix by a rotation matrix
     */
    void Rotate(float angle, float x, float y, float z);

    /**
     * Multiply the current matrix by a translation matrix
     */
    void Translate(float x, float y, float z);

    /**
     * Multiply the current matrix by a translation matrix
     */
    void Scale(float x, float y, float z);

    /**
     * Sets the manipulator
     */
    void SetManipulator(std::unique_ptr<Manipulator> manipulator);

    /**
     * Sets the camera
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

    /**
     * Sets the lights
     * Returns the light info by reference
     */
    void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights);

    /**
     * Sets the shadow map
     */
    bool SetupShadowMap(ShadowMapInfo& info);

    /**
     * Renders the shadow map
     */
    void RenderShadowMap(ShadowMapInfo& info);

    /**
     * Renders the node
     */
    void Render(const std::vector<LightInfo>& lights,
            const glm::mat4& projection, const glm::mat4& modelview,
            bool render_transparent, const ShadowMapInfo& sm_info);

private:
    std::unique_ptr<Manipulator> manipulator_;
    glm::mat4 matrix_;
    glm::mat4 inverse_;
};

#endif

