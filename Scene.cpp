/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <stdexcept>

#include <GL/glew.h>

#include "Scene.h"

Scene::Scene() :
    background_{0.8, 0.8, 0.8} {
}

void Scene::SetBackgroud(float r, float g, float b) {
    background_[0] = r;
    background_[1] = g;
    background_[2] = b;
}

void Scene::RenderScene() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(background_[0], background_[1], background_[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glm::mat4 projection, modelview;
    if (!SetupCamera(projection, modelview))
        throw std::runtime_error("Scene::Render(): Camera not found");
    std::vector<LightInfo> lights;
    SetupLight(modelview, lights);

    int draw_framebuffer = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer);

    ShadowMapInfo sm_info;
    SetupShadowMap(sm_info);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, sm_info.framebuffer);
    RenderShadowMap(sm_info);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer);
    Render(lights, projection, modelview, false, sm_info);
    Render(lights, projection, modelview, true, sm_info);
}

