/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "Light.h"

Light::Light() :
    light_id_(0),
    position_(0, 0, 0, 1),
    ambient_(0.2, 0.2, 0.2, 1),
    diffuse_(0.4, 0.4, 0.4, 1),
    specular_(0.4, 0.4, 0.4, 1),
    attenuation_(1, 0, 0),
    spot_enabled_(false),
    sm_enable_(false) {
}

void Light::SetPosition(float x, float y, float z, float w) {
    position_ = glm::vec4(x, y, z, w);
}

void Light::SetAmbient(float r, float g, float b, float a) {
    ambient_ = glm::vec4(r, g, b, a);
}

void Light::SetDiffuse(float r, float g, float b, float a) {
    diffuse_ = glm::vec4(r, g, b, a);
}

void Light::SetSpecular(float r, float g, float b, float a) {
    specular_ = glm::vec4(r, g, b, a);
}

void Light::SetAttenuation(float c, float l, float q) {
    attenuation_ = glm::vec3(c, l, q);
}

void Light::SetupSpot(float x, float y, float z, float cutoff, float exponent) {
    spot_enabled_ = true;
    spot_direction_ = glm::vec4(glm::normalize(glm::vec3(x, y, z)), 1);
    spot_cutoff_ = cos(cutoff * M_PI / 180.0);
    spot_exponent_ = exponent;
}

void Light::EnableShadowMap(const glm::vec3& center, const glm::vec3& up,
        const glm::mat4& projection) {
    sm_enable_ = true;
    sm_center_ = center;
    sm_up_ = up;
    sm_projection_ = projection;

    int width = kShadowmapWidth;
    int height = kShadowmapHeight;

    // Create Framebuffer
    glGenFramebuffers(1, &sm_framebuffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, sm_framebuffer_);

    // Create Renderbuffer
    glGenRenderbuffers(1, &sm_renderbuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, sm_renderbuffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER, sm_renderbuffer_);

    // Create texture
    glGenTextures(1, &sm_texture_);
    glBindTexture(GL_TEXTURE_2D, sm_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0,
            GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, sm_texture_, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Couldn't create shadowmap frame buffer");

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);  
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::SetupLight(const glm::mat4& modelview,
        std::vector<LightInfo>& lights) {
    if (!active_)
        return;

    auto normalmatrix = glm::transpose(glm::inverse(modelview));

    LightInfo info;
    info.position = modelview * position_;
    info.diffuse = diffuse_;
    info.specular = specular_;
    info.ambient = ambient_;
    info.attenuation = attenuation_;
    info.is_spot = spot_enabled_;
    info.direction = glm::normalize(glm::vec3(normalmatrix * spot_direction_));
    info.cutoff = spot_cutoff_;
    info.exponent = spot_exponent_;
    lights.push_back(info);
    light_id_ = lights.size() - 1;
}

bool Light::SetupShadowMap(ShadowMapInfo& info) {
    if (!active_)
        return false;

    info.projection = sm_projection_;
    info.modelview = glm::lookAt(glm::vec3(position_), sm_center_, sm_up_);
    info.light_id = light_id_;
    info.framebuffer = sm_framebuffer_;
    info.texture = sm_texture_;
    info.width = kShadowmapWidth;
    info.height = kShadowmapHeight;

    return true;
}

