/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 130

const float silhouette_size = 0.005;

in vec3 position;
in vec3 normal;

uniform mat4 mvp;

void main () {
    gl_Position = mvp * vec4(position + silhouette_size * normal, 1.0);
}

