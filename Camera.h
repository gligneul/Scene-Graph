/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <array>
#include <memory>

#include "Node.h"

class Manipulator;

/**
 * Scene's camera
 */
class Camera : public Node {
public:
    /**
     * Constructor
     */
    Camera();

    /**
     * Sets the eye coordinates
     * Default = (1, 0, 0)
     */
    void SetEye(float x, float y, float z);

    /**
     * Sets the center coordinates
     * Default = (0, 0, 0)
     */
    void SetCenter(float x, float y, float z);

    /**
     * Sets the up coordinates
     * Default = (0, 1, 0)
     */
    void SetUp(float x, float y, float z);

    /**
     * Sets the perspective parameters
     * Default 60, 1, 100
     */
    void SetPerspective(float fovy, float znear, float zfar);

    /**
     * Sets the manipulator
     */
    void SetManipulator(std::unique_ptr<Manipulator> manipulator);

    /**
     * Sets the camera
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

private:
    glm::vec3 eye_;
    glm::vec3 center_;
    glm::vec3 up_;
    float fovy_;
    float znear_;
    float zfar_;
    std::unique_ptr<Manipulator> manipulator_;
};

#endif

