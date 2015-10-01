/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <GL/gl.h>

#include "Material.h"

Material::Material() :
    ambient_{0.3, 0.3, 0.3, 1},
    diffuse_{1, 1, 1, 1},
    specular_{0.5, 0.5, 0.5, 1},
    shininess_(32) {
}

Material::Material(unsigned int color) :
    Material() {
    SetColor(color);
}

void Material::SetAmbient(float r, float g, float b, float a) {
    ambient_[0] = r;
    ambient_[1] = g;
    ambient_[2] = b;
    ambient_[3] = a;
}

void Material::SetDiffuse(float r, float g, float b, float a) {
    diffuse_[0] = r;
    diffuse_[1] = g;
    diffuse_[2] = b;
    diffuse_[3] = a;
}

void Material::SetSpecular(float r, float g, float b, float a) {
    specular_[0] = r;
    specular_[1] = g;
    specular_[2] = b;
    specular_[3] = a;
}

void Material::SetColor(unsigned int color) {
    float c[3] = {
        ((color >> 16) & 0xFF) / 256.0f,
        ((color >> 8) & 0xFF) / 256.0f,
        (color & 0xFF) / 256.0f
    };

    for (int i = 0; i < 3; i++) {
        ambient_[i] *= c[i];
        diffuse_[i] *= c[i];
    }
}

void Material::SetShininess(float shininess) {
    shininess_ = shininess;
}

void Material::Load() {
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_); 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_); 
}

void Material::Unload() {
    glPopAttrib();
}

