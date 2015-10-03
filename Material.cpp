/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <GL/gl.h>

#include "color.h"

#include "Material.h"

Material::Material(unsigned int color) :
    specular_{0.5, 0.5, 0.5, 1},
    shininess_{32} {
    SetColor(color);
}

void Material::SetAmbient(float r, float g, float b, float a) {
    ambient_ = {r, g, b, a};
}

void Material::SetDiffuse(float r, float g, float b, float a) {
    diffuse_ = {r, g, b, a};
}

void Material::SetSpecular(float r, float g, float b, float a) {
    specular_ = {r, g, b, a};
}

void Material::SetColor(unsigned int color) {
    std::array<float, 3> c = color::UnsignedToFloat3(color);
    for (int i = 0; i < 3; i++) {
        ambient_[i] = c[i] * 0.3;
        diffuse_[i] = c[i];
    }
}

void Material::SetShininess(float shininess) {
    shininess_ = shininess;
}

void Material::Load() {
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_.data()); 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_); 
}

void Material::Unload() {
    glPopAttrib();
}

