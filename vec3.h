/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef VEC3_H
#define VEC3_H

#include <array>
#include <cmath>

/**
 * 3D Vector auxiliary library
 */
namespace vec3 {

/**
 * 3D vectors are arrays
 */
template<typename T>
using V = std::array<T, 3>;

typedef V<float> Vf;
typedef V<double> Vd;

/**
 * Returns -u
 */
template<typename T>
V<T> neg(const V<T>& u) {
    return {-u[0], -u[1], -u[2]};
}

/**
 * Returns u + v
 */
template<typename T>
V<T> add(const V<T>& u, const V<T>& v) {
    return {u[0] + v[0], u[1] + v[1], u[2] + v[2]};
}

/**
 * Returns u + k
 */
template<typename T>
V<T> add(const V<T>& u, T k) {
    return {u[0] + k, u[1] + k, u[2] + k};
}

/**
 * Returns u - v
 */
template<typename T>
V<T> sub(const V<T>& u, const V<T>& v) {
    return {u[0] - v[0], u[1] - v[1], u[2] - v[2]};
}

/**
 * Returns u - k
 */
template<typename T>
V<T> sub(const V<T>& u, T k) {
    return {u[0] - k, u[1] - k, u[2] - k};
}

/**
 * Returns u * k
 */
template<typename T>
V<T> mul(const V<T>& u, T k) {
    return {u[0] * k, u[1] * k, u[2] * k};
}

/**
 * Returns u / k
 */
template<typename T>
V<T> div(const V<T>& u, T k) {
    return {u[0] / k, u[1] / k, u[2] / k};
}


/**
 * Returns u `dot` v
 */
template<typename T>
T dot(const V<T>& u, const V<T>& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

/**
 * Returns u `cross` v
 */
template<typename T>
V<T> cross(const V<T>& u, const V<T>& v) {
    return {
        u[1] * v[2] - u[2] * v[1],
        - u[0] * v[2] + u[2] * v[0],
        u[0] * v[1] - u[1] * v[0]
    };
}

/**
 * Returns |u|^2
 */
template<typename T>
T norm2(const V<T>& u) {
    return u[0] * u[0] + u[1] * u[1] + u[2] * u[2];
}

/**
 * Returns |u|
 */
template<typename T>
T norm(const V<T>& u) {
    return sqrt(norm2(u));
}

/**
 * Returns u / |u|
 */
template<typename T>
V<T> normalize(const V<T>& u) {
    const T n = norm(u);
    return {u[0] / n, u[1] / n, u[2] / n};
}

/**
 * Return acos( u `dot` v / |u| * |v|)
 */
template<typename T>
T angle(const V<T>& u, const V<T>& v) {
    return acos(dot(u, v) / (norm(u) * norm(v)));
}

}

#endif

