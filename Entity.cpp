/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include "Entity.h"

#include "Appearance.h"
#include "Shape.h"

Entity::Entity() :
    appearance_(nullptr),
    shape_(nullptr) {
}

void Entity::SetAppearance(Appearance* appearance) {
    appearance_ = appearance;
}

void Entity::SetShape(Shape* shape) {
    shape_ = shape;
}

void Entity::Render() {
    if (active_) {
        appearance_->Load();
        shape_->Draw();
        appearance_->Unload();
    }
}

