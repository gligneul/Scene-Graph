/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#version 130

in float light_intensity;

uniform vec4 color;

out vec4 frag_color;

void main () {
    frag_color = vec4(color.rgb * light_intensity, color.a);
}

