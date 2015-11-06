/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <GL/gl.h>

#include "Manipulator.h"
#include "Transform.h"
#include "invertMatrix.h"


Transform::Transform() :
    manipulator_{nullptr} {
    LoadIndentity();
}

void Transform::LoadIndentity() {
    pushMatrix();
    glLoadIdentity();
    popMatrix();
}

void Transform::Rotate(float angle, float x, float y, float z) {
    pushMatrix();
    glRotatef(angle, x, y, z);
    popMatrix();
}

void Transform::Translate(float x, float y, float z) {
    pushMatrix();
    glTranslatef(x, y, z);
    popMatrix();
}

void Transform::Scale(float x, float y, float z) {
    pushMatrix();
    glScalef(x, y, z);
    popMatrix();
}

bool Transform::SetupCamera() {
    if (!active_)
        return false;

    if (Group::SetupCamera()) {
        if (manipulator_)
            manipulator_->ApplyInv();
        glMultMatrixf(inv_);
        return true;
    }
    return false;
}

void Transform::SetManipulator(std::unique_ptr<Manipulator> manipulator) {
    manipulator_ = std::move(manipulator);
}

int Transform::SetupLight(int light_id) {
    if (!active_)
        return light_id;

    glPushMatrix();
    glMultMatrixf(matrix_);
    if (manipulator_ != nullptr)
        manipulator_->Apply();
    light_id = Group::SetupLight(light_id);
    glPopMatrix();
    return light_id;
}

void Transform::Render() {
    if (!active_)
        return;

    glPushMatrix();
    glMultMatrixf(matrix_);
    if (manipulator_ != nullptr)
        manipulator_->Apply();
    Group::Render();
    glPopMatrix();
}

void Transform::pushMatrix() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(matrix_);
}

void Transform::popMatrix() {
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);
    glPopMatrix();
    gluInvertMatrix(matrix_, inv_);
}

