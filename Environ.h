/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef ENVIRON_H
#define ENVIRON_H

#include <array>

class Environ {
public:
    /**
     * Default constructor
     */
    Environ() {}

    /**
     * Loads the environment configuration
     */
    void SetupEnvironment() {}

    /**
     * Sets the background color
     */
    void SetBackgroundColor(float r, float b, float g);

    /**
     * Sets the global ambient
     */
    void SetAmbient(float r, float g, float b);

    /**
     * Sets the fog
     */
    void SetFog(float r, float b, float g, float start, float end,
            float density);

private:
    std::array<float, 3> backgroud_;
    std::array<float, 3> ambient_;
    std::array<float, 3> fog_color_;
    float fog_start_, fog_end_, fog_density_;
};

#endif

