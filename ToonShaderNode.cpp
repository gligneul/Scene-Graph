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

static const glm::mat4 kShadowMapBiasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0);

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
    color_.a  = alpha;
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

void ToonShaderNode::RenderShadowMap(ShadowMapInfo& info,
        const glm::mat4& modelview) {
    if (!active_)
        return;

    auto mvp = info.projection * modelview;

    if (color_.a != 1) {
        info.mvp_transparent.push_back(mvp);
        return;
    }

    info.mvp.push_back(mvp);

    ShaderProgram *program = shared_->shadowmap_program;
    program->Enable();
    program->SetAttribLocation("position", 0);
    program->SetUniformMat4("mvp", mvp);
    mesh_->Draw();
    program->Disable();
}

void ToonShaderNode::Render(RenderInfo& info, const glm::mat4& modelview) {
    if (!active_ ||
        (info.render_transparent && color_.a == 1) ||
        (!info.render_transparent && color_.a < 1))
        return;

    auto mvp = info.projection * modelview;
    auto normalmatrix = glm::transpose(glm::inverse(modelview));
    auto sm_mvp = color_.a == 1 ? info.shadowmap.mvp[info.id] :
                                  info.shadowmap.mvp_transparent[info.id];

    if (color_.a == 1)
        RenderSilhouette(mvp);

    ShaderProgram *program = shared_->toon_program;
    program->Enable();

    LoadLights(program, info.lights);
    program->SetAttribLocation("position", 0);
    program->SetAttribLocation("normal", 1);
    program->SetUniformMat4("modelview", modelview);
    program->SetUniformMat4("normalmatrix", normalmatrix);
    program->SetUniformMat4("mvp", mvp);
    program->SetUniformVec4("color", color_);
    program->SetUniformMat4("sm_mvp", kShadowMapBiasMatrix * sm_mvp);
    program->SetUniformInteger("sm_light", info.shadowmap.light_id);
    
    glPushAttrib(GL_TEXTURE_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, info.shadowmap.texture);
    shared_->toon_program->SetUniformInteger("sm_texture", 0);

    mesh_->Draw();
    program->Disable();

    glPopAttrib();

    info.id++;
}

void ToonShaderNode::RenderSilhouette(const glm::mat4& mvp) {
    ShaderProgram *program = shared_->silhouette_program;
    program->Enable();
    program->SetAttribLocation("position", 0);
    program->SetAttribLocation("normal", 1);
    program->SetUniformFloat("silhouette", silhouette_);
    program->SetUniformMat4("mvp", mvp);
    mesh_->Draw();
    program->Disable();
}

