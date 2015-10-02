/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef COLOR_H
#define COLOR_H

#include <array>

namespace color {

/**
 * Converts a color RGB from unsigned int to 3 floats
 */
std::array<float, 3> UnsignedToFloat3(unsigned int color);

}

#endif

