/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef MESH_H
#define MESH_H

#include <array>
#include <string>
#include <vector>

#include "vec3.h"

#include "Shape.h"

class Mesh : public Shape {
public:
    /**
     * Default Constructor
     * Receives the path to the .off file
     * throws runtime_error if there is any io error or opengl error
     */
    Mesh(const std::string& path);

    /**
     * Destructor
     */
    ~Mesh();

    /**
     * Draws the shape
     */
    void Draw();

private:
    /**
     * Receives an index and returns the vertex
     */
    vec3::Vf GetVertex(unsigned int index, const float vertices[]);

    /**
     * Receives an index and sets the vertice
     */
    void SetVertex(unsigned int index, float vertices[],
            const vec3::Vf& vertex);

    /**
     * Reads the vertex information and the point information from file
     */
    void ReadFile(const std::string& path, std::vector<float>& vertices,
            std::vector<unsigned int>& indices);

    /**
     * Normalize the mesh in the range -0.5, 0.5 and center it in 0, 0, 0
     */
    void NormalizeVertices(std::vector<float>& vertices);

    /**
     * Calculate the normals based on the triangles
     */
    void CalculateNormals(const std::vector<float>& vertices,
            const std::vector<unsigned int>& indices,
            std::vector<float>& normals);

    std::vector<float> vertices_;
    std::vector<float> normals_;
    std::vector<unsigned int> indices_;
};

#endif

