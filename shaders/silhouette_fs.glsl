/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 130

out vec4 frag_color;

void main () {
    if (gl_FrontFacing)
        discard;
    else
        frag_color = vec4(0, 0, 0, 1);
}

