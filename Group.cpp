/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include "Group.h"

Group::~Group() {
}

void Group::AddNode(Node* node) {
    nodes_.push_back(node);
}

bool Group::SetupCamera(float* modelView) {
    if (active_)
        for (auto& node : nodes_)
            if (node->SetupCamera(modelView))
                return true;
    return false;
}

int Group::SetupLight(int light_id) {
    if (active_)
        for (auto& node : nodes_)
            light_id = node->SetupLight(light_id);
    return light_id;
}

void Group::Render() {
    if (active_)
        for (auto& node : nodes_)
            node->Render();
}

