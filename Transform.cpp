/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <cmath>

#include <glm/gtx/transform.hpp>

#include "Manipulator.h"

#include "Transform.h"

Transform::Transform() :
    manipulator_{nullptr} {
    LoadIndentity();
}

void Transform::LoadIndentity() {
    matrix_ = glm::mat4(1.0f);
    inverse_ = glm::mat4(1.0f);
}

void Transform::Rotate(float angle, float x, float y, float z) {
    matrix_ = glm::rotate(matrix_, (float)(angle * M_PI / 180.0),
            glm::vec3(x, y, z));
    inverse_ = glm::inverse(matrix_);
}

void Transform::Translate(float x, float y, float z) {
    matrix_ = glm::translate(matrix_, glm::vec3(x, y, z));
    inverse_ = glm::inverse(matrix_);
}

void Transform::Scale(float x, float y, float z) {
    matrix_ = glm::scale(matrix_, glm::vec3(x, y, z));
    inverse_ = glm::inverse(matrix_);
}

void Transform::SetManipulator(std::unique_ptr<Manipulator> manipulator) {
    manipulator_ = std::move(manipulator);
}

bool Transform::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
    if (!active_)
        return false;

    if (Group::SetupCamera(projection, modelview)) {
        if (manipulator_)
            modelview *= manipulator_->GetInverse();
        modelview *= inverse_;
        return true;
    }
    return false;
}

void Transform::SetupLight(const glm::mat4& modelview,
        std::vector<LightInfo>& lights) {
    if (!active_)
        return;

    glm::mat4 sub_mv = modelview;
    if (manipulator_)
        sub_mv *= manipulator_->GetMatrix();
    Group::SetupLight(sub_mv * matrix_, lights);
}

bool Transform::SetupShadowMap(ShadowMapInfo& info) {
    if (!active_)
        return false;

    if (Group::SetupShadowMap(info)) {
        if (manipulator_)
            info.modelview *= manipulator_->GetInverse();
        info.modelview *= inverse_;
        return true;
    }
    return false;
}

void Transform::RenderShadowMap(ShadowMapInfo& info,
        const glm::mat4& modelview) {
    if (!active_)
        return;

    glm::mat4 sub_modelview = modelview;
    if (manipulator_)
        sub_modelview *= manipulator_->GetMatrix();
    sub_modelview *= matrix_;
    Group::RenderShadowMap(info, sub_modelview);
}

void Transform::Render(RenderInfo& info, const glm::mat4& modelview) {
    if (!active_)
        return;

    glm::mat4 sub_modelview = modelview;
    if (manipulator_)
        sub_modelview *= manipulator_->GetMatrix();
    sub_modelview *= matrix_;
    Group::Render(info, sub_modelview);
}

