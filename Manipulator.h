/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <array>

#include <glm/glm.hpp>

class Manipulator {
public:
    /**
     * Constructor
     */
    Manipulator();
    
    /**
     * Accumulates the manipulator matrix
     */
    void Apply();

    /**
     * Accumulates the inverse of the manipulator matrix
     */
    void ApplyInv();

    /**
     * Sets the reference point (world center)
     */
    void SetReferencePoint(float x, float y, float z);

    /**
     * Sets whether each axis is inverted or not
     */
    void SetInvertAxis(bool invertX, bool invertY = false);

    /**
     * Mouse button function
     */
    void GlutMouse(int button, int state, int x, int y);

    /**
     * Mouse motion function
     */
    void GlutMotion(int x, int y);

private:
    enum class Operation {
        kRotation,
        kZoom,
        kNone
    };

    const float kZoomScale = 1.0f;

    /** Verifies the k_button state and sets the k_operation */
    template<int k_button, Operation k_operation>
    void SetOperation(int button, int state, int x, int y);

    /** Computes the sphere vector for rotation */
    glm::vec3 computeSphereCoordinates(int x, int y);

    std::array<float, 3> reference_;
    glm::mat4 matrix_;
    glm::mat4 inv_;
    Operation operation_;
    float x_, y_;
    glm::vec3 v_;
    bool invertX_, invertY_;
};

#endif

