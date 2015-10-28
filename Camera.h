/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
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
    void SetEye(double x, double y, double z);

    /**
     * Sets the center coordinates
     * Default = (0, 0, 0)
     */
    void SetCenter(double x, double y, double z);

    /**
     * Sets the up coordinates
     * Default = (0, 1, 0)
     */
    void SetUp(double x, double y, double z);

    /**
     * Sets the perspective parameters
     * Default 60, 1, 100
     */
    void SetPerspective(double fovy, double znear, double zfar);

    /**
     * Sets the manipulator
     */
    void SetManipulator(std::unique_ptr<Manipulator> manipulator);

    /**
     * Sets the camera
     * Returns true if the camera has been set
     */
    bool SetupCamera();

private:
    std::array<double, 3> eye_;
    std::array<double, 3> center_;
    std::array<double, 3> up_;
    double fovy_;
    double znear_;
    double zfar_;
    std::unique_ptr<Manipulator> manipulator_;
};

#endif

