/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
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
    void SetPos(float x, float y, float z, float w = 1.0f);

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
     * Setup spot
     */
    void SetupSpot(float x, float y, float z, float cutoff, float exponent);

    /**
     * Sets the lights
     * Receives the light id
     * Returns the next light id
     */
    int SetupLight(int light_id);

private:
    std::array<float, 4> pos_;
    std::array<float, 4> ambient_;
    std::array<float, 4> diffuse_;
    std::array<float, 4> specular_;
    bool spot_enabled_;
    std::array<float, 3> spot_direction_;
    float spot_cutoff_;
    float spot_exponent_;
};

#endif

