/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include "Node.h"

Node::Node() :
    active_{true} {
}

Node::~Node() {
}

bool Node::SetupCamera(float* modelView) {
    (void)modelView;
    return false;
}

int Node::SetupLight(int light_id) {
    return light_id;
}

void Node::Render() {
}

void Node::SetActive(bool active) {
    active_ = active;
}

bool Node::GetActive() {
    return active_;
}

