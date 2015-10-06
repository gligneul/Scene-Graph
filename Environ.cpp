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
    background_{0, 0, 0},
    ambient_{0.1, 0.1, 0.1},
    fog_type_{FogType::kFogDisabled},
    fog_color_{0.5, 0.5, 0.5},
    fog_start_{0},
    fog_end_{1},
    fog_density_{0.1} {
}

void Environ::SetBackgroundColor(unsigned int color) {
    background_ = color::UnsignedToFloat3(color);
}

void Environ::SetAmbient(float r, float g, float b) {
    ambient_ = {r, g, b};
}

void Environ::SetFogType(FogType type) {
    fog_type_ = type;
}

void Environ::SwitchFog() {
    SetFogType((FogType)(((int)fog_type_ + 1) % (int)FogType::kFogNTypes));
}

void Environ::SetFogColor(unsigned int color) {
    fog_color_ = color::UnsignedToFloat3(color);
}

void Environ::SetLinearFog(float start, float end) {
    fog_start_ = start;
    fog_end_ = end;
}

void Environ::SetExponentialFog(float density) {
    fog_density_ = density;
}

void Environ::Load() {
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_LIGHTING_BIT | GL_FOG_BIT);

    glClearColor(background_[0], background_[1], background_[2], 1.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_.data());

    if (fog_type_ == FogType::kFogDisabled) {
        glDisable(GL_FOG);
    } else {
        glEnable(GL_FOG);
        switch (fog_type_) {
            case FogType::kFogLinear:
                glFogi(GL_FOG_MODE, GL_LINEAR);
                break;
            case FogType::kFogExp:
                glFogi(GL_FOG_MODE, GL_EXP);
                break;
            case FogType::kFogExp2:
                glFogi(GL_FOG_MODE, GL_EXP2);
                break;
            default:
                break;
        }

        glFogfv(GL_FOG_COLOR, fog_color_.data());
        glFogf(GL_FOG_START, fog_start_);
        glFogf(GL_FOG_END, fog_end_);
        glFogf(GL_FOG_DENSITY, fog_density_);
    }
}

void Environ::Unload() {
    glPopAttrib();
}

