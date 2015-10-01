/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef SCENE_H
#define SCENE_H

#include "Group.h"

class Environ;

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
     * Destructor
     */
    ~Scene();

    /**
     * Sets the enviroment
     */
    void SetEnviron(Environ* environ);

    /**
     * Renders the scene
     * Throws runtime_error if there's no camera
     */
    void Render();

private:
    Environ* environ_;
};

#endif

