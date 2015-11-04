/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelview;
uniform mat4 projection;

out float light_intensity;

void main () {
    vec4 light_position = modelview * vec4(0.0, 3.0, 0.0, 1.0);

    vec4 global_position = modelview * vec4(position, 1.0);

    mat4 normalmatrix = transpose(inverse(modelview));
    vec3 global_normal = normalize(vec3(normalmatrix * vec4(normal, 1.0)));

    vec3 l = normalize(vec3(light_position - global_position));

    light_intensity = 0.2 + clamp(dot(global_normal, l), 0.0, 0.8);

    gl_Position = projection * global_position;
}

