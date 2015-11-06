/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <stdexcept>

#include <GL/gl.h>

#include "Scene.h"

Scene::Scene() {
}

void Scene::RenderScene() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glm::mat4 projection, modelview;
    if (!SetupCamera(projection, modelview))
        throw std::runtime_error("Scene::Render(): Camera not found");
    std::vector<LightInfo> lights;
    SetupLight(modelview, lights);
    Render(lights, projection, modelview);
}

