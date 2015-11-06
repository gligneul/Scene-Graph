/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef TOONSHADERNODE_H
#define TOONSHADERNODE_H

#include <memory>

#include "Node.h"

class Mesh;
class ShaderProgram;

class ToonShaderNode : public Node {
public:
    /**
     * Constructor
     */
    ToonShaderNode();

    /**
     * Destructor
     */
    ~ToonShaderNode();

    /**
     * Sets the color
     */
    void SetColor(unsigned int color, float alpha = 1.0f);

    /**
     * Sets the mesh
     */
    void SetMesh(std::shared_ptr<Mesh> mesh);

    /**
     * Renders the node
     */
    void Render();

private:
    static ShaderProgram *program_;

    std::shared_ptr<Mesh> mesh_;
    float color_[4];
};

#endif

