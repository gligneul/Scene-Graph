/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef MVECTOR_H
#define MVECTOR_H

#include <cmath>

/**
 * Math's vector auxiliary functions
 */
namespace mvector {

/**
 * Dot Product w = u x v
 */
template<typename T>
void cross(T *u, T *v, T *w) {
    w[0] = u[1] * v[2] - u[2] * v[1];
    w[1] = - u[0] * v[2] + u[2] * v[0];
    w[2] = u[0] * v[1] - u[1] * v[0];
}

/**
 * Length of u
 */
template<typename T>
T length(T *u) {
    return sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
}

}

#endif

