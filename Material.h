/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <array>

#include "Appearance.h"

class Material : public Appearance {
public:
    /**
     * Constructor
     * Receives the material color
     */
    Material(unsigned int color = 0x888888);

    /**
     * Sets the ambient component
     */
    void SetAmbient(float r, float g, float b, float a = 1.0f);
    
    /**
     * Sets the diffuse component
     */
    void SetDiffuse(float r, float g, float b, float a = 1.0f);

    /**
     * Sets the specular component
     * Default = 0.5, 0.5, 0.5, 1.0
     */
    void SetSpecular(float r, float g, float b, float a = 1.0f);

    /**
     * Sets the shininess
     * Default = 32
     */
    void SetShininess(float shininess);

    /**
     * Sets the ambient and diffuse by the color
     * Receives a color in the format 0xRRGGBB
     */
    void SetColor(unsigned int color);

    /**
     * Loads the appearance
     */
    void Load();

    /**
     * Unloads the appearance
     */
    void Unload();

private:
    std::array<float, 4> ambient_;
    std::array<float, 4> diffuse_;
    std::array<float, 4> specular_;
    float shininess_;
};

#endif

