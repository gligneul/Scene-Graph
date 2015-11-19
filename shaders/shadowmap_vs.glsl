/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 130

in vec3 position;

uniform mat4 mvp;

void main () {
    gl_Position = mvp * vec4(position, 1.0);
}

