/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <glm/gtx/transform.hpp>

#include "Mesh.h"
#include "ShaderProgram.h"

#include "ToonShaderNode.h"

ToonShaderNode::Shared *ToonShaderNode::shared_ = nullptr;

ToonShaderNode::ToonShaderNode() :
    mesh_{nullptr},
    color_{0.3f, 0.3f, 0.3f, 1.0f} {

    if (!shared_) {
        shared_ = new Shared;
        shared_->toon_program = new ShaderProgram("shaders/toonshader");
        shared_->silhouette_program = new ShaderProgram("shaders/silhouette");
    }
}

ToonShaderNode::~ToonShaderNode() {
}

void ToonShaderNode::SetColor(unsigned int color, float alpha) {
    color_ = glm::vec4(
       ((color >> 16) & 0xFF) / 255.0f,
       ((color >> 8) & 0xFF) / 255.0f,
       (color & 0xFF) / 255.0f,
       alpha
    );
}

void ToonShaderNode::SetMesh(std::shared_ptr<Mesh> mesh) {
    mesh_ = mesh;
}

void ToonShaderNode::Render(const std::vector<LightInfo>& lights,
        const glm::mat4& projection, const glm::mat4& modelview) {
    (void)lights;

    auto mvp = projection * modelview;
    auto normalmatrix = glm::transpose(glm::inverse(modelview));

    shared_->silhouette_program->Enable();
    shared_->silhouette_program->SetAttribLocation("position", 0);
    shared_->silhouette_program->SetAttribLocation("normal", 1);
    shared_->silhouette_program->SetUniformMat4("mvp", mvp);
    mesh_->Draw();

    shared_->toon_program->Enable();
    shared_->toon_program->SetAttribLocation("position", 0);
    shared_->toon_program->SetAttribLocation("normal", 1);
    shared_->toon_program->SetUniformMat4("modelview", modelview);
    shared_->toon_program->SetUniformMat4("normalmatrix", normalmatrix);
    shared_->toon_program->SetUniformMat4("mvp", mvp);
    shared_->toon_program->SetUniformVec4("color", color_);
    mesh_->Draw();
    shared_->toon_program->Disable();
}

