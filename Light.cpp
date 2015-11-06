/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include "Light.h"

Light::Light() :
    position_(0, 0, 0, 1),
    ambient_(0.2, 0.2, 0.2, 1),
    diffuse_(0.4, 0.4, 0.4, 1),
    specular_(0.4, 0.4, 0.4, 1),
    spot_enabled_(false),
    spot_direction_(1, 0, 0),
    spot_cutoff_(45),
    spot_exponent_(64) {
}

void Light::SetPosition(float x, float y, float z, float w) {
    position_ = glm::vec4(x, y, z, w);
}

void Light::SetAmbient(float r, float g, float b, float a) {
    ambient_ = glm::vec4(r, g, b, a);
}

void Light::SetDiffuse(float r, float g, float b, float a) {
    diffuse_ = glm::vec4(r, g, b, a);
}

void Light::SetSpecular(float r, float g, float b, float a) {
    specular_ = glm::vec4(r, g, b, a);
}

void Light::SetupSpot(float x, float y, float z, float cutoff, float exponent) {
    spot_enabled_ = true;
    spot_direction_ = glm::vec3(x, y, z);
    spot_cutoff_ = cutoff;
    spot_exponent_ = exponent;
}

void Light::SetupLight(const glm::mat4& modelview,
        std::vector<LightInfo>& lights) {
    if (!active_)
        return;

    LightInfo info;
    info.position = modelview * position_;
    info.diffuse = diffuse_;
    info.specular = specular_;
    info.ambient = ambient_;
    info.is_spot = spot_enabled_;
    info.direction = spot_direction_;
    info.cutoff = spot_cutoff_;
    info.exponent = spot_exponent_;
    lights.push_back(info);
}

