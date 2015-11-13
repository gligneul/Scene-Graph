/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>

#include "Camera.h"

#include "Manipulator.h"

Camera::Camera() :
    eye_{1, 0, 0},
    center_{0, 0, 0},
    up_{0, 1, 0},
    fovy_{50},
    znear_{1},
    zfar_{100},
    manipulator_{} {
}

void Camera::SetEye(float x, float y, float z) {
    eye_ = glm::vec3(x, y, z);
}

void Camera::SetCenter(float x, float y, float z) {
    center_ = glm::vec3(x, y, z);
}

void Camera::SetUp(float x, float y, float z) {
    up_ = glm::vec3(x, y, z);
}

void Camera::SetPerspective(float fovy, float znear, float zfar) {
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

    int vp[4]; 
    glGetIntegerv(GL_VIEWPORT, vp); 
    projection = glm::perspective((float)(fovy_ * M_PI / 180.0),
            (float)vp[2]/vp[3], znear_, zfar_);
    modelview = glm::lookAt(eye_, center_, up_);
    if (manipulator_)
        modelview *= manipulator_->GetMatrix(glm::normalize(center_ - eye_));

    return true;
}

