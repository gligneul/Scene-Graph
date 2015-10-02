/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <fstream>
#include <limits>
#include <stdexcept>

#include <GL/gl.h>

#include "vec3.h"

#include "Mesh.h"

Mesh::Mesh(const std::string& path) {
    ReadFile(path, vertices_, indices_);
    NormalizeVertices(vertices_);
    CalculateNormals(vertices_, indices_, normals_);
}

Mesh::~Mesh() {
}

void Mesh::Draw() {
    glBegin(GL_TRIANGLES);

    for (size_t i = 0; i < indices_.size(); ++i) {
        glNormal3fv(normals_.data() + 3 * indices_[i]);
        glVertex3fv(vertices_.data() + 3 * indices_[i]);
    }
    
    glEnd();
}

vec3::Vf Mesh::GetVertex(unsigned int index, const float vertices[]) {
    return {
        vertices[index * 3],
        vertices[index * 3 + 1],
        vertices[index * 3 + 2]
    };
}

void Mesh::SetVertex(unsigned int index, float vertices[],
        const vec3::Vf& vertex) {
    vertices[index * 3] = vertex[0];
    vertices[index * 3 + 1] = vertex[1];
    vertices[index * 3 + 2] = vertex[2];
}

void Mesh::ReadFile(const std::string& path, std::vector<float>& vertices,
        std::vector<unsigned int>& indices) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    input.open(path);

    size_t nVertices, nTriangles, nQuads;
    input.ignore(3);
    input >> nVertices >> nTriangles >> nQuads;

    vertices.resize(nVertices * 3);
    for (size_t i = 0; i < vertices.size(); ++i)
        input >> vertices[i];
    
    indices.resize( (nTriangles + 2 * nQuads) * 3 );
    size_t idx = 0;
    for (size_t i = 0; i < nTriangles + nQuads; ++i) {
        int polygon;
        input >> polygon;

        if (polygon == 3) {
            input >> indices[idx++];
            input >> indices[idx++];
            input >> indices[idx++];
        } else {
            float quad[4];
            input >> quad[0] >> quad[1] >> quad[2] >> quad[3];
            indices[idx++] = quad[0];
            indices[idx++] = quad[1];
            indices[idx++] = quad[2];
            indices[idx++] = quad[2];
            indices[idx++] = quad[3];
            indices[idx++] = quad[0];
        }
    }
}

void Mesh::NormalizeVertices(std::vector<float>& vertices) {
    vec3::Vf min;
    min.fill(std::numeric_limits<float>::max());
    float max = std::numeric_limits<float>::min();

    for (size_t i = 0; i < vertices.size(); i += 3) {
        for (size_t j = 0; j < 3; ++j) {
            min[j] = std::min(min[j], vertices[i + j]);
            max = std::max(max, vertices[i + j]);
        }
    }

    for (size_t i = 0; i < vertices.size() / 3; ++i) {
        vec3::Vf vertex = GetVertex(i, vertices.data());
        vec3::Vf normalized =
                vec3::sub(vec3::div(vec3::sub(vertex, min), max), 0.5f);
        SetVertex(i, vertices.data(), normalized);
    }
}

void Mesh::CalculateNormals(const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices, std::vector<float>& normals) {

    // Initialize the normals
    std::vector<vec3::Vf> pre_normals(vertices.size() / 3);
    for (size_t i = 0; i < pre_normals.size(); ++i) {
        pre_normals[i] = {0, 0, 0};
    }

    // Calculate the normals for each triangle vertex
    for (size_t i = 0; i < indices.size(); i += 3) {
        // Triangle vertices' indices
        unsigned int v[3] = {indices[i], indices[i + 1], indices[i + 2]};

        // Triangle's vertices
        vec3::Vf triangle[3] = {
            GetVertex(v[0], vertices.data()),
            GetVertex(v[1], vertices.data()),
            GetVertex(v[2], vertices.data())
        };

        // Vectors created by the triangle's vertexes
        vec3::Vf v0_to_v1 = vec3::sub(triangle[1], triangle[0]);
        vec3::Vf v0_to_v2 = vec3::sub(triangle[2], triangle[0]);
        vec3::Vf v1_to_v2 = vec3::sub(triangle[2], triangle[1]);

        // Angle between the vectors
        float angle[3];
        angle[0] = vec3::angle(v0_to_v1, v0_to_v2);
        angle[1] = vec3::angle(v1_to_v2, vec3::neg(v0_to_v1));
        angle[2] = M_PI - angle[0] - angle[1];

        // Triangle's normal
        vec3::Vf t_normal = vec3::normalize(vec3::cross(v0_to_v1, v0_to_v2));

        // Vertex normal += triangle normal * vertex angle in the triangle
        for (size_t j = 0; j < 3; ++j)
            pre_normals[v[j]] = vec3::add(pre_normals[v[j]],
                    vec3::mul(t_normal, angle[j]));
    }

    normals.resize(vertices.size());
    for (size_t i = 0; i < pre_normals.size(); ++i)
        SetVertex(i, normals.data(), vec3::normalize(pre_normals[i]));
}
