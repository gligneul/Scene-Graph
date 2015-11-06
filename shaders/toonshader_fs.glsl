/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 130

in vec3 frag_light;
in vec3 frag_normal;

uniform vec4 color;

out vec4 frag_color;

void main () {
    float light_intensity = max(dot(normalize(frag_normal),
            normalize(frag_light)), 0);
    light_intensity += 0.2;
    frag_color = vec4(color.rgb * light_intensity, color.a);
}

