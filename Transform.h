/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Group.h"

class Manipulator;

class Transform : public Group {
public:
    /**
     * Constructor
     * Loads the identity by default
     */
    Transform();

    /**
     * Destructor
     */
    ~Transform();
    
    /**
     * Loads the identity matrix
     */
    void LoadIndentity();

    /**
     * Multiply the current matrix by a rotation matrix
     */
    void Rotate(float angle, float x, float y, float z);

    /**
     * Multiply the current matrix by a translation matrix
     */
    void Translate(float x, float y, float z);

    /**
     * Multiply the current matrix by a translation matrix
     */
    void Scale(float x, float y, float z);

    /**
     * Sets the camera
     * Receives the reference to the output modelView
     * Returns true if the camera has been set
     */
    bool SetupCamera(float* modelView);

    /**
     * Sets the manipulator that will be loaded after the transformation
     */
    void SetManipulator(Manipulator* manipulator);

    /**
     * Sets the lights
     * Receives the light id
     * Returns the next light id
     */
    int SetupLight(int light_id);

    /**
     * Renders the entities
     */
    void Render();

private:
    Manipulator* manipulator_;
    float matrix_[16];
};

#endif
