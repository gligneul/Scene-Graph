/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <GL/glut.h>

#include "Sphere.h"

Sphere::Sphere(float radius) :
    radius_(radius) {
}

void Sphere::Draw() {
    glutSolidSphere(radius_, 32, 32);
}

