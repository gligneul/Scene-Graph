/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <GL/gl.h>

#include "color.h"

#include "Environ.h"

Environ::Environ() :
    backgroud_{0, 0, 0},
    ambient_{0.1, 0.1, 0.1},
    fog_enable_{false},
    fog_color_{1, 1, 1},
    fog_start_{0},
    fog_end_{1} {
}

void Environ::SetBackgroundColor(unsigned int color) {
    backgroud_ = color::UnsignedToFloat3(color);
}

void Environ::SetAmbient(float r, float g, float b) {
    ambient_ = {r, g, b};
}

void Environ::SetFog(unsigned int color, float start, float end) {
    fog_enable_ = true;
    fog_color_ = color::UnsignedToFloat3(color);
    fog_start_ = start;
    fog_end_ = end;
}

void Environ::SetupEnvironment() {
    glClearColor(backgroud_[0], backgroud_[1], backgroud_[2], 1.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_.data());
    if (fog_enable_) {
        glEnable(GL_FOG);
        glFogfv(GL_FOG_COLOR, fog_color_.data());
        glFogf(GL_FOG_START, fog_start_);
        glFogf(GL_FOG_END, fog_end_);
        glFogi(GL_FOG_MODE, GL_LINEAR);
    } else {
        glDisable(GL_FOG);
    }
}

