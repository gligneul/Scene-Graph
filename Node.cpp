/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include "Node.h"

Node::Node() :
    active_{true} {
}

Node::~Node() {
}

bool Node::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
    (void)projection;
    (void)modelview;
    return false;
}

void Node::SetupLight(const glm::mat4& modelview, 
        std::vector<LightInfo>& lights) {
    (void)modelview;
    (void)lights;
}

void Node::Render(const std::vector<LightInfo>& lights,
        const glm::mat4& projection, const glm::mat4& modelview) {
    (void)lights;
    (void)projection;
    (void)modelview;
}

void Node::SetActive(bool active) {
    active_ = active;
}

bool Node::GetActive() {
    return active_;
}

