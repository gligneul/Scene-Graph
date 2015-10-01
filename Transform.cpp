/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <GL/gl.h>

#include "Manipulator.h"
#include "Transform.h"

Transform::Transform() :
    manipulator_(nullptr) {
    LoadIndentity();
}

void Transform::LoadIndentity() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);
    glPopMatrix();
}

void Transform::Rotate(float angle, float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(matrix_);
    glRotatef(angle, x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);
    glPopMatrix();
}

void Transform::Translate(float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(matrix_);
    glTranslatef(x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);
    glPopMatrix();
}

void Transform::Scale(float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(matrix_);
    glScalef(x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);
    glPopMatrix();
}

bool Transform::SetupCamera(float* modelView) {
    if (!active_)
        return false;

    glPushMatrix();
    glMultMatrixf(matrix_);
    if (manipulator_ != nullptr)
        manipulator_->Apply();
    bool cameraSet = Group::SetupCamera(modelView);
    glPopMatrix();
    return cameraSet;
}

void Transform::SetManipulator(Manipulator* manipulator) {
    manipulator_ = manipulator;
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

