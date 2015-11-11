/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Pedro Igor P. Sampaio 1011381
 * Trabalho - Projeto Final
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "Transform.h"

class Engine {
public:
    typedef std::shared_ptr<Transform> JeepNode;

    /**
     * Constructor
     */
    Engine(JeepNode jeep,
           JeepNode frontleftwheel_direction,
           JeepNode frontrightwheel_direction,
           JeepNode frontleftwheel_speed,
           JeepNode frontrightwheel_speed,
           JeepNode backleftwheel_speed,
           JeepNode backrightwheel_speed,
           JeepNode steering_wheel);

    /**
     * Keyboard function
     */
    void Keyboard(unsigned char key);

    /**
     * Update function
     */
    void Update();

private:
    /* Constants */
    const float kSpeedIncrement = 0.5;
    const float kSpeedMax = 10;
    const float kAlphaIncrement = 2;
    const float kAlphaMax = 33.3;
    const float kSteeringWheelIncrement = 2 * kAlphaIncrement;

    /* Attributes */
    JeepNode jeep_;
    JeepNode frontleftwheel_direction_;
    JeepNode frontrightwheel_direction_;
    JeepNode frontleftwheel_speed_;
    JeepNode frontrightwheel_speed_;
    JeepNode backleftwheel_speed_;
    JeepNode backrightwheel_speed_;
    JeepNode steering_wheel_;
    float speed_;
    float alpha_;
    int last_time_;
};

#endif

