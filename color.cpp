/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include "color.h"

namespace color {

std::array<float, 3> UnsignedToFloat3(unsigned int color) {
    return {
        ((color >> 16) & 0xFF) / 256.0f,
        ((color >> 8) & 0xFF) / 256.0f,
        (color & 0xFF) / 256.0f
    };
}

}

