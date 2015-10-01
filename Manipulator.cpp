/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <algorithm>
#include <cmath>

#include <GL/gl.h>
#include <GL/glut.h>

#include "Manipulator.h"
#include "mvector.h"

Manipulator::Manipulator() :
    reference_{0, 0, 0},
    matrix_{1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1},
    operation_(Operation::kNone),
    x_{0},
    y_{0},
    v_{0, 0, 0} {
}

void Manipulator::Apply() {
    glTranslatef(reference_[0], reference_[1], reference_[2]);
    glMultMatrixf(matrix_.data());
    glTranslatef(-reference_[0], -reference_[1], -reference_[2]);
}

void Manipulator::SetReferencePoint(float x, float y, float z) {
    reference_ = {x, y, z};
}

void Manipulator::GlutMouse(int button, int state, int x, int y) {
    SetOperation<GLUT_LEFT_BUTTON, Operation::kRotation>(button, state, x, y);
    SetOperation<GLUT_RIGHT_BUTTON, Operation::kZoom>(button, state, x, y);
}

void Manipulator::GlutMotion(int x, int y) {
    if (operation_ == Operation::kNone)
        return;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (operation_ == Operation::kRotation) {
        std::array<float, 3> v = computeSphereCoordinates(x, y);
        std::array<float, 3> w;
        mvector::cross(v_.data(), v.data(), w.data());
        float theta = asin(mvector::length(w.data())) * 180 / M_PI;
        glRotatef(theta, w[0], w[1], w[2]);
        v_ = v;
    } else if (operation_ == Operation::kZoom) {
        int vp[4]; 
        glGetIntegerv(GL_VIEWPORT, vp);
        float dy = y - y_;
        float f = dy / vp[3];
        float scale = 1 + kZoomScale * f;
        glScalef(scale, scale, scale);
    }

    glMultMatrixf(matrix_.data());
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix_.data());
    glPopMatrix();

    x_ = x;
    y_ = y;
}

template<int k_button, Manipulator::Operation k_operation>
void Manipulator::SetOperation(int button, int state, int x, int y) {
    if (button == k_button) {
        if (state == GLUT_DOWN && operation_ == Operation::kNone) {
            operation_ = k_operation;
            x_ = x;
            y_ = y;
            v_ = computeSphereCoordinates(x, y);
        } else if (state == GLUT_UP && operation_ == k_operation) {
            operation_ = Operation::kNone;
        }
    }
}

std::array<float, 3> Manipulator::computeSphereCoordinates(int x, int y) {
    int vp[4]; 
    glGetIntegerv(GL_VIEWPORT, vp);
    const float w = vp[2];
    const float h = vp[3];

    const float radius = std::min(w / 2.0f, h / 2.0f);
    std::array<float, 3> v = {
        (x - w / 2.0f) / radius,
        (h - y - h / 2.0f) / radius,
    };

    const float dist = hypot(v[0], v[1]);
    if (dist > 1.0f) {
        v[0] /= dist;
        v[1] /= dist;
        v[2] = 0;
    } else {
        v[2] = sqrt(1 - v[0] * v[0] - v[1] * v[1]);
    }

    return v;
}

