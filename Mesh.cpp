/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <cinttypes>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

#include <GL/glew.h>

#include "Mesh.h"

Mesh::Mesh(const std::string& path) :
    vbo_{0, 0, 0},
    vao_(0) {
    ReadFile(path, vertices_, normals_, indices_);
    NormalizeVertices(vertices_);
    InitializeVBO(vertices_, normals_, indices_);
}

Mesh::~Mesh() {
    if (vao_ != 0) {
        glDeleteVertexArrays(1, &vao_);
        glDeleteBuffers(3, vbo_);
    }
}

void Mesh::Draw() {
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::GetMesh(std::vector<float>& vertices, std::vector<float>& normals,
        std::vector<unsigned int>& indices) {
    vertices = vertices_;
    normals = normals_;
    indices = indices_;
}

glm::vec3 Mesh::GetVertex(unsigned int index, const float vertices[]) {
    return glm::vec3(
        vertices[index * 3],
        vertices[index * 3 + 1],
        vertices[index * 3 + 2]
    );
}

void Mesh::SetVertex(unsigned int index, float vertices[],
        const glm::vec3& vertex) {
    vertices[index * 3] = vertex[0];
    vertices[index * 3 + 1] = vertex[1];
    vertices[index * 3 + 2] = vertex[2];
}

void Mesh::ReadFile(const std::string& path, std::vector<float>& vertices,
        std::vector<float>& normals, std::vector<unsigned int>& indices) {
    std::string extension = path.substr(path.rfind('.'));
    if (extension == ".off") {
        ReadOFF(path, vertices, indices);
        CalculateNormals(vertices, indices, normals);
    } else if (extension == ".msh") {
        ReadMSH(path, vertices, normals, indices);
    } else {
        throw std::runtime_error("Unknown mesh extension: " + extension);
    }
}

void Mesh::ReadOFF(const std::string& path, std::vector<float>& vertices,
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

void Mesh::ReadMSH(const std::string& path, std::vector<float>& vertices,
        std::vector<float>& normals, std::vector<unsigned int>& indices) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    input.open(path);

    size_t nVertices, nTriangles;
    input >> nVertices >> nTriangles;

    vertices.resize(nVertices * 3);
    normals.resize(nVertices * 3);
    for (size_t i = 0; i < nVertices; ++i) {
        int id;
        input >> id;
        input >> vertices[3 * i]
              >> vertices[3 * i + 1]
              >> vertices[3 * i + 2];
        input >> normals[3 * i]
              >> normals[3 * i + 1]
              >> normals[3 * i + 2];
    }

    indices.resize(nTriangles * 3);
    for (size_t i = 0; i < nTriangles; ++i) {
        int id;
        input >> id;
        input >> indices[3 * i]
              >> indices[3 * i + 1]
              >> indices[3 * i + 2];
    }
}

void Mesh::NormalizeVertices(std::vector<float>& vertices) {
    glm::vec3 min(std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    float max = std::numeric_limits<float>::min();

    for (size_t i = 0; i < vertices.size(); i += 3) {
        for (size_t j = 0; j < 3; ++j) {
            min[j] = std::min(min[j], vertices[i + j]);
            max = std::max(max, vertices[i + j]);
        }
    }

    for (size_t i = 0; i < vertices.size() / 3; ++i) {
        glm::vec3 vertex = GetVertex(i, vertices.data());
        glm::vec3 normalized = (vertex - min) / max - 0.5f;
        SetVertex(i, vertices.data(), normalized);
    }
}

void Mesh::CalculateNormals(const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices, std::vector<float>& normals) {

    // Initialize the normals
    std::vector<glm::vec3> pre_normals(vertices.size() / 3);
    for (size_t i = 0; i < pre_normals.size(); ++i) {
        pre_normals[i] = {0, 0, 0};
    }

    // Calculate the normals for each triangle vertex
    for (size_t i = 0; i < indices.size(); i += 3) {
        // Triangle vertices' indices
        unsigned int v[3] = {indices[i], indices[i + 1], indices[i + 2]};

        // Triangle's vertices
        glm::vec3 triangle[3] = {
            GetVertex(v[0], vertices.data()),
            GetVertex(v[1], vertices.data()),
            GetVertex(v[2], vertices.data())
        };

        // Vectors created by the triangle's vertexes
        glm::vec3 v0_to_v1 = triangle[1] - triangle[0];
        glm::vec3 v0_to_v2 = triangle[2] - triangle[0];
        glm::vec3 v1_to_v2 = triangle[2] - triangle[1];

        auto angleBetween = [](const glm::vec3& u, const glm::vec3& v) {
            return acos(glm::dot(u, v) / (glm::length(u) * glm::length(v)));
        };

        // Angle between the vectors
        float angle[3];
        angle[0] = angleBetween(v0_to_v1, v0_to_v2);
        angle[1] = angleBetween(v1_to_v2, -v0_to_v1);
        angle[2] = M_PI - angle[0] - angle[1];

        // Triangle's normal
        glm::vec3 t_normal = glm::normalize(glm::cross(v0_to_v1, v0_to_v2));

        // Vertex normal += triangle normal * vertex angle in the triangle
        for (size_t j = 0; j < 3; ++j)
            pre_normals[v[j]] = pre_normals[v[j]] + t_normal * angle[j];
    }

    normals.resize(vertices.size());
    for (size_t i = 0; i < pre_normals.size(); ++i)
        SetVertex(i, normals.data(), glm::normalize(pre_normals[i]));
}

void Mesh::InitializeVBO(const std::vector<float>& vertices,
        const std::vector<float>& normals,
        const std::vector<unsigned int> indices) {

    glGenBuffers(3, vbo_);
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
            vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), 
            normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
             indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

