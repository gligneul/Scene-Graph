/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <algorithm>

#include <GL/glew.h>
#include <glm/gtx/transform.hpp>

#include "Mesh.h"
#include "ShaderProgram.h"

#include "ToonShaderNode.h"

ToonShaderNode::Shared *ToonShaderNode::shared_ = nullptr;

ToonShaderNode::ToonShaderNode(unsigned int color, float silhouette) :
    mesh_{nullptr},
    silhouette_(silhouette) {
    SetColor(color);
    if (!shared_) {
        shared_ = new Shared;
        shared_->toon_program = new ShaderProgram("shaders/toonshader");
        shared_->silhouette_program = new ShaderProgram("shaders/silhouette");
        shared_->shadowmap_program = new ShaderProgram("shaders/shadowmap");
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

void ToonShaderNode::SetOpacity(float alpha) {
    color_.w  = alpha;
}

void ToonShaderNode::SetMesh(std::shared_ptr<Mesh> mesh) {
    mesh_ = mesh;
}

void ToonShaderNode::SetMesh(const std::string& mesh) {
    mesh_ = std::make_shared<Mesh>(mesh);
}

void ToonShaderNode::LoadLights(ShaderProgram *program,
        const std::vector<LightInfo>& lights) {
    unsigned int nlights = std::min(lights.size(), kMaxLights);
    program->SetUniformInteger("nlights", nlights);
    for (size_t i = 0; i < nlights; ++i) {
        auto id = "lights[" + std::to_string(i) + "].";
        program->SetUniformVec4(id + "position", lights[i].position);
        program->SetUniformVec4(id + "diffuse", lights[i].diffuse);
        program->SetUniformVec4(id + "specular", lights[i].specular);
        program->SetUniformVec4(id + "ambient", lights[i].ambient);
        program->SetUniformVec3(id + "attenuation", lights[i].attenuation);
        program->SetUniformInteger(id + "is_spot", lights[i].is_spot);
        program->SetUniformVec3(id + "direction", lights[i].direction);
        program->SetUniformFloat(id + "cutoff", lights[i].cutoff);
        program->SetUniformFloat(id + "exponent", lights[i].exponent);
    }
}

void ToonShaderNode::RenderShadowMap(ShadowMapInfo& info) {
    if (!active_ || color_.a != 1)
        return;

    auto mvp = info.projection * info.modelview;
    shared_->shadowmap_program->Enable();
    shared_->shadowmap_program->SetAttribLocation("position", 0);
    shared_->shadowmap_program->SetUniformMat4("mvp", mvp);
    mesh_->Draw();
    shared_->shadowmap_program->Disable();
}

void ToonShaderNode::Render(const std::vector<LightInfo>& lights,
        const glm::mat4& projection, const glm::mat4& modelview,
        bool render_transparent, const ShadowMapInfo& sm_info) {
    if (!active_)
        return;

    if ((render_transparent && color_.a == 1)
        || (!render_transparent && color_.a < 1))
        return;

    auto mvp = projection * modelview;
    auto normalmatrix = glm::transpose(glm::inverse(modelview));

    glm::mat4 bias_matrix(
            0.5, 0.0, 0.0, 0.0,
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
    );

    if (color_.a == 1) {
        shared_->silhouette_program->Enable();
        shared_->silhouette_program->SetAttribLocation("position", 0);
        shared_->silhouette_program->SetAttribLocation("normal", 1);
        shared_->silhouette_program->SetUniformFloat("silhouette", silhouette_);
        shared_->silhouette_program->SetUniformMat4("mvp", mvp);
        mesh_->Draw();
        shared_->silhouette_program->Disable();
    }

    glPushAttrib(GL_TEXTURE_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sm_info.texture);

    shared_->toon_program->Enable();

    LoadLights(shared_->toon_program, lights);
    shared_->toon_program->SetAttribLocation("position", 0);
    shared_->toon_program->SetAttribLocation("normal", 1);
    shared_->toon_program->SetUniformMat4("modelview", modelview);
    shared_->toon_program->SetUniformMat4("normalmatrix", normalmatrix);
    shared_->toon_program->SetUniformMat4("mvp", mvp);
    shared_->toon_program->SetUniformVec4("color", color_);
    shared_->toon_program->SetUniformMat4("sm_mvp",
            bias_matrix * sm_info.projection * sm_info.modelview);
    shared_->toon_program->SetUniformInteger("sm_light", sm_info.light_id);
    shared_->toon_program->SetUniformInteger("sm_texture", 0);
    
    mesh_->Draw();

    shared_->toon_program->Disable();

    glPopAttrib();
}

