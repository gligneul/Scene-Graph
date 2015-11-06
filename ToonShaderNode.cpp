/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <GL/glew.h>

#include "Mesh.h"
#include "ShaderProgram.h"
#include "invertMatrix.h"

#include "ToonShaderNode.h"

ShaderProgram *ToonShaderNode::program_ = nullptr;

ToonShaderNode::ToonShaderNode() :
    mesh_{nullptr},
    color_{0.3f, 0.3f, 0.3f, 1.0f} {

    if (!program_)
        program_ = new ShaderProgram("shaders/toonshader");
}

ToonShaderNode::~ToonShaderNode() {
}

void ToonShaderNode::SetColor(unsigned int color, float alpha) {
    color_[0] = ((color >> 16) & 0xFF) / 255.0f;
    color_[1] = ((color >> 8) & 0xFF) / 255.0f;
    color_[2] = (color & 0xFF) / 255.0f;
    color_[3] = alpha;
}

void ToonShaderNode::SetMesh(std::shared_ptr<Mesh> mesh) {
    mesh_ = mesh;
}

void ToonShaderNode::Render() {
    unsigned int program = program_->GetHandle();
    glUseProgram(program);

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 0, "normal");

    float modelview[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
    GLuint modelview_location = glGetUniformLocation(program, "modelview");
    glUniformMatrix4fv(modelview_location, 1, false, modelview);

    float normalmatrix[16];
    gluInvertMatrix(modelview, normalmatrix);
    GLuint normalmatrix_loc = glGetUniformLocation(program, "normalmatrix");
    glUniformMatrix4fv(normalmatrix_loc, 1, true, normalmatrix);

    float mvp[16];
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glMultMatrixf(modelview);
    glGetFloatv(GL_PROJECTION_MATRIX, mvp);
    glPopMatrix();
    glPopAttrib();
    GLuint mvp_location = glGetUniformLocation(program, "mvp");
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, mvp);

    GLuint color_location = glGetUniformLocation(program, "color");
    glUniform4fv(color_location, 1, color_);

    mesh_->Draw();

    glUseProgram(0);
}

