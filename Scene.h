/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "Group.h"

/**
 * The scene root
 */
class Scene : public Group {
public:
    /**
     * Default Constructor
     */
    Scene();

    /**
     * Sets the background color
     */
    void SetBackgroud(float r, float g, float b);

    /**
     * Renders the scene
     * Throws runtime_error if there's no camera
     */
    void RenderScene();

private:
    float background_[3];
};

#endif

