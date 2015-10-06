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
    enum class FogType {
        kFogLinear = 0,
        kFogExp,
        kFogExp2,
        kFogDisabled,
        kFogNTypes
    };

    /**
     * Default constructor
     */
    Environ();

    /**
     * Sets the background color
     */
    void SetBackgroundColor(unsigned int color);

    /**
     * Sets the global ambient
     */
    void SetAmbient(float r, float g, float b);

    /**
     * Sets the fog type
     */
    void SetFogType(FogType type);

    /**
     * Switch to the next fog type in the enum
     */
    void SwitchFog();

    /**
     * Set the fog color
     */
    void SetFogColor(unsigned int color);

    /**
     * Sets the linear fog parameters
     */
    void SetLinearFog(float start, float end);

    /**
     * Sets the exponential fog parameters
     */
    void SetExponentialFog(float density);

    /**
     * Loads the enviroment
     */
    void Load();

    /**
     * Unloads the enviroment
     */
    void Unload();

private:
    std::array<float, 3> background_;
    std::array<float, 3> ambient_;
    FogType fog_type_;
    std::array<float, 3> fog_color_;
    float fog_start_, fog_end_, fog_density_;
};

#endif

