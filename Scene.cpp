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
    environ_(nullptr) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    for (int i = 0; i < 8; i++)
        glEnable(GL_LIGHT0 + i);
}

void Scene::SetEnviron(Environ* environ) {
    environ_ = environ;
}

void Scene::Render() {
    //environ_->SetupEnvironment();

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
}

