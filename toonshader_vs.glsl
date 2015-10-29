/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#version 130

in vec3 vertex;
in vec3 normal;

uniform mat4 modelview;
uniform mat4 projection;

out float light_intensity;

void main () {
    vec4 light_position = modelview * vec4(0, 3, 0, 1);

    vec4 global_position = modelview * vec4(vertex, 1.0);
    vec3 global_normal = normalize(vec3(modelview * vec4(normal, 1.0)));
    vec3 s = vec3(light_position - global_position);
    light_intensity = max(dot(s, global_normal), 0.0);

    gl_Position = projection * global_position;
}

