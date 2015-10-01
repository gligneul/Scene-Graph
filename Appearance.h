/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef APPEARANCE_H
#define APPEARANCE_H

class Appearance {
public:
    /**
     * Virtual destructor
     */
    virtual ~Appearance() {}

    /**
     * Loads the appearance
     */
    virtual void Load() = 0;

    /**
     * Unloads the appearance
     */
    virtual void Unload() = 0;
};

#endif

