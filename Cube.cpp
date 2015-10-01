/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <GL/gl.h>

#include "Cube.h"

Cube::Cube(float dx, float dy, float dz) :
    dx_(dx),
    dy_(dy),
    dz_(dz) {
}

void Cube::SetDimensions(float dx, float dy, float dz) {
    dx_ = dx;
    dy_ = dy;
    dz_ = dz;
}

void Cube::Draw() {
    float vertices[8][3] = {
        {-0.5, -0.5, -0.5},
        {-0.5, -0.5, 0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, 0.5, 0.5},
        {0.5, -0.5, -0.5},
        {0.5, -0.5, 0.5},
        {0.5, 0.5, -0.5},
        {0.5, 0.5, 0.5},
    };

    int faces[6][4] = {
        {1, 5, 7, 3},
        {0, 4, 5, 1},
        {5, 4, 6, 7},
        {2, 3, 7, 6},
        {0, 1, 3, 2},
        {0, 2, 6, 4},
    };

    float normals[6][3] = {
        {0, 0, 1},
        {0, -1, 0},
        {1, 0, 0},
        {0, 1, 0},
        {-1, 0, 0},
        {0, 0, -1}
    };

    glPushMatrix();
    glScalef(dx_, dy_, dz_);

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        glNormal3fv(normals[i]);
        for (int j = 0; j < 4; j++)
            glVertex3fv(vertices[faces[i][j]]);
    }
    glEnd();

    glPopMatrix();
}

