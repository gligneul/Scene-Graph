/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include "Mesh.h"
#include "ShaderProgram.h"

#include "ToonShaderNode.h"

ShaderProgram *ToonShaderNode::program_ = nullptr;

ToonShaderNode::ToonShaderNode() :
    mesh_{nullptr},
    color_{0.3f, 0.3f, 0.3f, 1.0f} {

    if (!program_)
        program_ = new ShaderProgram("shaders/toonshader");
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
    program_->Enable();
    program_->SetAttribLocation("position", 0);
    program_->SetAttribLocation("normal", 1);
    program_->SetUniformMat4("modelview", modelview);
    program_->SetUniformMat4("normalmatrix",
            glm::transpose(glm::inverse(modelview)));
    program_->SetUniformMat4("mvp", projection * modelview);
    program_->SetUniformVec4("color", color_);
    mesh_->Draw();
    program_->Disable();
}

