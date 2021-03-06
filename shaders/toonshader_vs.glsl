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
uniform mat4 sm_mvp;

out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_sm_position;

void main () {
    frag_position = vec3(modelview * vec4(position, 1.0));
    frag_normal = normalize(vec3(normalmatrix * vec4(normal, 1.0)));
    vec4 sm_position = sm_mvp * vec4(position, 1.0);
    frag_sm_position = sm_position.xyz / sm_position.w;
    gl_Position = mvp * vec4(position, 1.0);
}

