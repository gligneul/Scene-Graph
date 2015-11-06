/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <GL/gl.h>
#include <GL/glu.h>

#include "Camera.h"

#include "Manipulator.h"

Camera::Camera() :
    eye_{1, 0, 0},
    center_{0, 0, 0},
    up_{0, 1, 0},
    fovy_{60},
    znear_{1},
    zfar_{100},
    manipulator_{} {
}

void Camera::SetEye(double x, double y, double z) {
    eye_ = {x, y, z};
}

void Camera::SetCenter(double x, double y, double z) {
    center_ =  {x, y, z};
}

void Camera::SetUp(double x, double y, double z) {
    up_ = {x, y, z};
}

void Camera::SetPerspective(double fovy, double znear, double zfar) {
    fovy_ = fovy;
    znear_ = znear;
    zfar_ = zfar;
}

void Camera::SetManipulator(std::unique_ptr<Manipulator> manipulator) {
    manipulator_ = std::move(manipulator);
}

bool Camera::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
    if (!active_)
        return false;

    // Sets the perspective
    int vp[4]; 
    glGetIntegerv(GL_VIEWPORT, vp); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    gluPerspective(fovy_, (float)vp[2]/vp[3], znear_, zfar_);
    float projectionmatrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, projectionmatrix);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            projection[i][j] = projectionmatrix[4 * i + j];

    // Sets the modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_[0], eye_[1], eye_[2], center_[0], center_[1], center_[2],
            up_[0], up_[1], up_[2]);
    float modelviewmatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewmatrix);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            modelview[i][j] = modelviewmatrix[4 * i + j];
    if (manipulator_)
        modelview *= manipulator_->GetMatrix();

    return true;
}

