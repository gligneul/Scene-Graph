/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include "Light.h"

#include <GL/gl.h>

Light::Light() :
    pos_{0, 0, 0, 1},
    ambient_{0.2, 0.2, 0.2, 1},
    diffuse_{0.4, 0.4, 0.4, 1},
    specular_{0.4, 0.4, 0.4, 1},
    spot_enabled_{false},
    spot_direction_{1, 0, 0},
    spot_cutoff_{45},
    spot_exponent_{64} {
}

void Light::SetPos(float x, float y, float z, float w) {
    pos_ = {x, y, z, w};
}

void Light::SetAmbient(float r, float g, float b, float a) {
    ambient_ = {r, g, b, a};
}

void Light::SetDiffuse(float r, float g, float b, float a) {
    diffuse_ = {r, g, b, a};
}

void Light::SetSpecular(float r, float g, float b, float a) {
    specular_ = {r, g, b, a};
}

void Light::SetupSpot(float x, float y, float z, float cutoff, float exponent) {
    spot_enabled_ = true;
    spot_direction_ = {x, y, z};
    spot_cutoff_ = cutoff;
    spot_exponent_ = exponent;
}

int Light::SetupLight(int light_id) {
    if (!active_)
        return light_id;

    glEnable(light_id);
    glLightfv(light_id, GL_POSITION, pos_.data());
    glLightfv(light_id, GL_AMBIENT, ambient_.data());
    glLightfv(light_id, GL_DIFFUSE, diffuse_.data());
    glLightfv(light_id, GL_SPECULAR, specular_.data());
    
    if (spot_enabled_) {
        glLightfv(light_id, GL_SPOT_DIRECTION, spot_direction_.data());
        glLightf(light_id, GL_SPOT_CUTOFF, spot_cutoff_);
        glLightf(light_id, GL_SPOT_EXPONENT, spot_exponent_);
    }

    return light_id + 1;
}

