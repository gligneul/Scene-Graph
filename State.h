/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#ifndef STATE_H
#define STATE_H

class State {
public:
    /**
     * Virtual destructor
     */
    virtual ~State() {}

    /**
     * Loads the state
     */
    virtual void Load() = 0;

    /**
     * Unloads the state
     */
    virtual void Unload() = 0;
};

#endif

