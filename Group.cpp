/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include "Group.h"

Group::~Group() {
}

void Group::AddNode(std::shared_ptr<Node> node) {
    nodes_.push_back(node);
}

bool Group::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
    if (active_)
        for (auto& node : nodes_)
            if (node->SetupCamera(projection, modelview))
                return true;
    return false;
}

void Group::SetupLight(const glm::mat4& modelview, 
        std::vector<LightInfo>& lights) {
    if (active_)
        for (auto& node : nodes_)
            node->SetupLight(modelview, lights);
}

bool Group::SetupShadowMap(ShadowMapInfo& info) {
    if (active_)
        for (auto& node : nodes_)
            if (node->SetupShadowMap(info))
                return true;
    return false;
}

void Group::RenderShadowMap(ShadowMapInfo& info) {
    if (active_)
        for (auto& node : nodes_)
            node->RenderShadowMap(info);
}

void Group::Render(const std::vector<LightInfo>& lights,
        const glm::mat4& projection, const glm::mat4& modelview,
        bool render_transparent, const ShadowMapInfo& sm_info) {
    if (active_)
        for (auto& node : nodes_)
            node->Render(lights, projection, modelview, render_transparent,
                    sm_info);
}

