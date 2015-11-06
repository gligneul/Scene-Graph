/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 130

in vec3 position;
in vec3 normal;

uniform mat4 modelview;
uniform mat4 normalmatrix;
uniform mat4 mvp;

out vec3 frag_light;
out vec3 frag_normal;

void main () {
    vec3 light_position = vec3(modelview * vec4(0, 3, 0, 1));

    vec3 mv_position = vec3(modelview * vec4(position, 1.0));
    frag_light = normalize(light_position - mv_position);
    frag_normal = vec3(normalmatrix * vec4(normal, 1.0));
    gl_Position = mvp * vec4(position, 1.0);
}

