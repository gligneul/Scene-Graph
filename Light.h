/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <array>

#include "Node.h"

class Light : public Node {
public:
    /**
     * Default constructor
     */
    Light();

    /**
     * Sets the light position
     * Default = 0, 0, 0
     */
    void SetPosition(float x, float y, float z, float w = 1.0f);

    /**
     * Sets the ambient component
     * Default = 0.2, 0.2, 0.2, 1.0
     */
    void SetAmbient(float r, float g, float b, float a = 1.0f);
    
    /**
     * Sets the diffuse component
     * Default = 0.4, 0.4, 0.4, 1.0
     */
    void SetDiffuse(float r, float g, float b, float a = 1.0f);

    /**
     * Sets the specular component
     * Default = 0.4, 0.4, 0.4, 1.0
     */
    void SetSpecular(float r, float g, float b, float a = 1.0f);

    /**
     * Sets the attenuation: 1 / (c + l*d + q*d^2)
     * Default = (1, 0, 0)
     */
    void SetAttenuation(float c, float l, float q);

    /**
     * Setup spot
     */
    void SetupSpot(float x, float y, float z, float cutoff, float exponent);

    /**
     * Enables the shadow map
     */
    void EnableShadowMap(const glm::vec3& center, const glm::vec3& up,
            float fovy, float near, float far);

    /**
     * Sets the lights
     * Returns the light info by reference
     */
    void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights);

    /**
     * Sets the shadow map
     */
    bool SetupShadowMap(ShadowMapInfo& info);

private:
    int light_id_;
    glm::vec4 position_;
    glm::vec4 ambient_;
    glm::vec4 diffuse_;
    glm::vec4 specular_;
    glm::vec3 attenuation_;
    bool spot_enabled_;
    glm::vec4 spot_direction_;
    float spot_cutoff_;
    float spot_exponent_;
    bool sm_enable_;
    glm::vec3 sm_center_;
    glm::vec3 sm_up_;
    float sm_fovy_;
    float sm_near_;
    float sm_far_;
    unsigned int sm_framebuffer_;
    unsigned int sm_renderbuffer_;
    unsigned int sm_texture_;
};

#endif

