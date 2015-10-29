/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#version 130

in vec3 vp;

uniform mat4 modelview;
uniform mat4 projection;

void main () {
    gl_Position = projection * modelview * vec4(vp, 1.0);
}

