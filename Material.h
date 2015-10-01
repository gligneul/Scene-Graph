/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Appearance.h"

class Material : public Appearance {
public:
    /**
     * Default constructor
     */
    Material();

    /**
     * Constructor that receives the material color
     */
    Material(unsigned int color);

    /**
     * Sets the ambient component
     * Default = 0.25, 0.25, 0.25, 1.0
     */
    void SetAmbient(float r, float g, float b, float a = 1.0f);
    
    /**
     * Sets the diffuse component
     * Default = 0.75, 0.75, 0.75, 1.0
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
    float ambient_[4];
    float diffuse_[4];
    float specular_[4];
    float shininess_;
};

#endif

