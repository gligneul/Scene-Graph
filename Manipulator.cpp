/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <iostream>
#include <algorithm>
#include <cmath>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/gl.h>

#include "Manipulator.h"
#include "invertMatrix.h"
#include "vec3.h"

Manipulator::Manipulator() :
    reference_{0, 0, 0},
    matrix_(1.0),
    inv_(1.0),
    operation_{Operation::kNone},
    x_{0},
    y_{0},
    v_(0, 0, 0),
    invertX_{false},
    invertY_{false} {
}

void Manipulator::Apply() {
    glTranslatef(reference_[0], reference_[1], reference_[2]);
    glMultMatrixf(glm::value_ptr(matrix_));
    glTranslatef(-reference_[0], -reference_[1], -reference_[2]);
}

void Manipulator::ApplyInv() {
    glTranslatef(-reference_[0], -reference_[1], -reference_[2]);
    glMultMatrixf(glm::value_ptr(inv_));
    glTranslatef(reference_[0], reference_[1], reference_[2]);
}

void Manipulator::SetReferencePoint(float x, float y, float z) {
    reference_ = {x, y, z};
}

void Manipulator::GlutMouse(int button, int state, int x, int y) {
    SetOperation<0, Operation::kRotation>(button, state, x, y);
    SetOperation<2, Operation::kZoom>(button, state, x, y);
}

void Manipulator::SetInvertAxis(bool invertX, bool invertY) {
    invertX_ = invertX;
    invertY_ = invertY;
}

void Manipulator::GlutMotion(int x, int y) {
    if (operation_ == Operation::kNone)
        return;

    if (operation_ == Operation::kRotation) {
        glm::vec3 v = computeSphereCoordinates(x, y);
        glm::vec3 w = glm::cross(v_, v);
        float theta = asin(glm::length(w));
        if (theta != 0)
            matrix_ = glm::rotate(theta, w) * matrix_;
        v_ = v;
    } else if (operation_ == Operation::kZoom) {
        int vp[4]; 
        glGetIntegerv(GL_VIEWPORT, vp);
        float dy = y - y_;
        float f = dy / vp[3];
        float scale = 1 + kZoomScale * f;
        matrix_ = glm::scale(glm::vec3(scale, scale, scale)) * matrix_;
    }

    inv_ = glm::inverse(matrix_);
    x_ = x;
    y_ = y;
}

template<int k_button, Manipulator::Operation k_operation>
void Manipulator::SetOperation(int button, int state, int x, int y) {
    if (button == k_button) {
        if (state == 0 && operation_ == Operation::kNone) {
            operation_ = k_operation;
            x_ = x;
            y_ = y;
            v_ = computeSphereCoordinates(x, y);
        } else if (state == 1 && operation_ == k_operation) {
            operation_ = Operation::kNone;
        }
    }
}

glm::vec3 Manipulator::computeSphereCoordinates(int x, int y) {
    int vp[4]; 
    glGetIntegerv(GL_VIEWPORT, vp);
    const float w = vp[2];
    const float h = vp[3];

    if (invertX_) x = w - x;
    if (invertY_) y = h - y;

    const float radius = std::min(w / 2.0f, h / 2.0f);
    float vx = (x - w / 2.0f) / radius;
    float vy = (h - y - h / 2.0f) / radius;
    float vz = 0;

    const float dist = hypot(vx, vy);
    if (dist > 1.0f) {
        vx /= dist;
        vy /= dist;
    } else {
        vz = sqrt(1 - vx * vx - vy * vy);
    }

    return glm::vec3(vx, vy, vz);
}

