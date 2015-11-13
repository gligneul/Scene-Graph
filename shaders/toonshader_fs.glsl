/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 130

struct LightInfo {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 ambient;
    vec3 attenuation;
    bool is_spot;
    vec3 direction;
    float cutoff;
    float exponent;
};

const int MAX_LIGHTS = 8;
const int NUM_COLORS = 5;
const vec3 GLOBAL_AMBIENT = vec3(0.2, 0.2, 0.2);

in vec3 frag_position;
in vec3 frag_normal;

uniform vec4 color;
uniform int nlights;
uniform LightInfo lights[MAX_LIGHTS];

out vec4 frag_color;

vec3 compute_light_intensity(LightInfo light, vec3 frag_normal) {
    vec3 light_position = light.position.xyz / light.position.w;
    vec3 frag2light = normalize(light_position - frag_position);
    float diff = max(dot(frag_normal, frag2light), 0);
    float dist = length(light_position - frag_position);
    float att = 1 / (light.attenuation.x + light.attenuation.y * dist
                     + light.attenuation.y * dist * dist);
    vec3 intensity = att * vec3(light.ambient + diff * light.diffuse);

    if (light.is_spot) {
        float kspot = max(dot(-frag2light, light.direction), 0);
        if (kspot > light.cutoff) {
            kspot = pow(kspot, light.exponent);
            return kspot * intensity;
        }
        return vec3(0, 0, 0); 
    }

    return intensity;
}

void main () {
    vec3 frag_normal_n = normalize(frag_normal);
    vec3 frag_light = vec3(0, 0, 0);
    for (int i = 0; i < nlights; i++)
        frag_light += compute_light_intensity(lights[i], frag_normal_n);
    frag_light += GLOBAL_AMBIENT;
    frag_light = floor(frag_light * NUM_COLORS) / NUM_COLORS;
    frag_color = vec4(color.rgb * frag_light, color.a);
}

