/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <cmath>
#include <cstdio>

#include <GL/gl.h>
#include <GL/glu.h>

#include "Cylinder.h"

Cylinder::Cylinder(float base, float top, float height, bool closed) :
    base_{base},
    top_{top},
    height_{height},
    closed_{closed},
    quadric_{gluNewQuadric()} {
}

Cylinder::~Cylinder() {
    gluDeleteQuadric(quadric_);
}

void Cylinder::SetDimensions(float base, float top, float height) {
    base_ = base;
    top_ = top;
    height_ = height;
}

void Cylinder::SetClosed(bool closed) {
    closed_ = closed;
}

void Cylinder::Draw() {
    if (closed_)
        gluDisk(quadric_, 0, base_, 30, 30);

    gluCylinder(quadric_, base_, top_, height_, 30, 30);

    if (closed_) {
        glPushMatrix();
        glTranslatef(0, 0, height_);
        gluDisk(quadric_, 0, top_, 30, 30);
        glPopMatrix();
    }
}

