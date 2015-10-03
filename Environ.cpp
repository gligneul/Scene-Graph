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
    fog_type_{FogType::kFogDisabled} {
}

void Environ::SetBackgroundColor(unsigned int color) {
    std::array<float, 3> backgroud = color::UnsignedToFloat3(color);
    glClearColor(backgroud[0], backgroud[1], backgroud[2], 1.0f);
}

void Environ::SetAmbient(float r, float g, float b) {
    std::array<float, 3> ambient = {r, g, b};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient.data());
}

void Environ::SetFogType(FogType type) {
    fog_type_ = type;
    if (type != FogType::kFogDisabled)
        glEnable(GL_FOG);
    else
        glDisable(GL_FOG);

    switch (type) {
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
}

void Environ::SwitchFog() {
    SetFogType((FogType)(((int)fog_type_ + 1) % (int)FogType::kFogNTypes));
}

void Environ::SetFogColor(unsigned int color) {
    glFogfv(GL_FOG_COLOR, color::UnsignedToFloat3(color).data());
}

void Environ::SetLinearFog(float start, float end) {
    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);
}

void Environ::SetExponentialFog(float density) {
    glFogf(GL_FOG_DENSITY, density);
}

