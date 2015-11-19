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
    ToonShaderNode(unsigned int color = 0x111111, float silhouette = 0.005);

    /**
     * Destructor
     */
    ~ToonShaderNode();

    /**
     * Sets the color
     */
    void SetColor(unsigned int color, float alpha = 1.0f);

    /**
     * Sets the opacity
     */
    void SetOpacity(float alpha);

    /**
     * Sets the mesh
     */
    void SetMesh(std::shared_ptr<Mesh> mesh);

    /**
     * Sets the mesh
     */
    void SetMesh(const std::string& mesh);

    /**
     * Renders the shadow map
     */
    void RenderShadowMap(ShadowMapInfo& info);

    /**
     * Renders the node
     */
    void Render(const std::vector<LightInfo>& lights,
            const glm::mat4& projection, const glm::mat4& modelview,
            bool render_transparent, const ShadowMapInfo& sm_info);

private:
    /**
     * Sets the uniform light data
     */
    void LoadLights(ShaderProgram *program,
            const std::vector<LightInfo>& lights);

    // Constants
    const size_t kMaxLights = 8;

    // Shared between instances
    struct Shared {
        ShaderProgram *toon_program;
        ShaderProgram *silhouette_program;
        ShaderProgram *shadowmap_program;
    };
    static Shared *shared_;

    // Attributes
    std::shared_ptr<Mesh> mesh_;
    glm::vec4 color_;
    float silhouette_;
};

#endif

