/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <stdexcept>

#include <GL/gl.h>

#include "Environ.h"

#include "Scene.h"

Scene::Scene() :
    environ_{nullptr} {
}

void Scene::SetEnviron(std::unique_ptr<Environ> environ) {
    environ_ = std::move(environ);
}

void Scene::Render() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

    if (environ_)
        environ_->Load();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float modelView[16];
    if (!SetupCamera(modelView))
        throw std::runtime_error("Scene::Render(): Camera not found");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(modelView);
    SetupLight(GL_LIGHT0);
    Group::Render();

    if (environ_)
        environ_->Unload();
}

