/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Pedro Igor P. Sampaio 1011381
 * Trabalho - Projeto Final
 */

#include <GL/glut.h>

#include "Engine.h"

static float clamp(float value, float max) {
    if (value > max)
        return max;
    else if (value < -max)
        return -max;
    else
        return value;
}

Engine::Engine(JeepNode jeep,
               JeepNode frontleftwheel_direction,
               JeepNode frontrightwheel_direction,
               JeepNode frontleftwheel_speed,
               JeepNode frontrightwheel_speed,
               JeepNode backleftwheel_speed,
               JeepNode backrightwheel_speed,
               JeepNode steering_wheel) :
    jeep_(jeep),
    frontleftwheel_direction_(frontleftwheel_direction),
    frontrightwheel_direction_(frontrightwheel_direction),
    frontleftwheel_speed_(frontleftwheel_speed),
    frontrightwheel_speed_(frontrightwheel_speed),
    backleftwheel_speed_(backleftwheel_speed),
    backrightwheel_speed_(backrightwheel_speed),
    steering_wheel_(steering_wheel),
    speed_(0),
    alpha_(0),
    last_time_(glutGet(GLUT_ELAPSED_TIME)) {
}

void Engine::Keyboard(unsigned char key) {
    switch (key) {
        case 'w':
            speed_ = clamp(speed_ + kSpeedIncrement, kSpeedMax);
            break;
        case 's':
            speed_ = clamp(speed_ - kSpeedIncrement, kSpeedMax);
            break;
        case ' ':
            speed_ = 0;
            break;
        case 'a':
            if (alpha_ >= kAlphaMax)
                break;
            alpha_ = alpha_ + kAlphaIncrement;
            frontleftwheel_direction_->Rotate(kAlphaIncrement, 0, 0, 1);
            frontrightwheel_direction_->Rotate(kAlphaIncrement, 0, 0, 1);
            steering_wheel_->Rotate(kSteeringWheelIncrement, -0.7935, 0, .6085);
            break;
        case 'd':
            if (alpha_ <= -kAlphaMax)
                break;
            alpha_ = alpha_ - kAlphaIncrement;
            frontleftwheel_direction_->Rotate(-kAlphaIncrement, 0, 0, 1);
            frontrightwheel_direction_->Rotate(-kAlphaIncrement, 0, 0, 1);
            steering_wheel_->Rotate(-kSteeringWheelIncrement, -.7935, 0, .6085);
            break;
    }
}

void Engine::Update() {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    float dt = (curr_time - last_time_) / 1000.0f;
    last_time_ = curr_time;

    // Move jeep
    float vx = speed_ * cos(alpha_ * (M_PI / 180.0));
    float vy = speed_ * sin(alpha_ * (M_PI / 180.0));
    float dx = vx * dt;
    float theta = vy / 2.5;
    if (theta != 0) {
        jeep_->Rotate(dt * theta * (180.0 / M_PI), 0, 0, 1);
    }
    jeep_->Translate(dx, 0, 0);

    // Rotate back wheels
    float backwheeltheta = (dx / (0.438 * 2)) * (180.0 / M_PI);
    backrightwheel_speed_->Rotate(backwheeltheta, 0, 1, 0);
    backleftwheel_speed_->Rotate(backwheeltheta, 0, 1, 0);

    // Rotate front wheels
    float frontwheeltheta = ((speed_ * dt) / (0.438 * 2)) * (180.0 / M_PI);
    frontrightwheel_speed_->Rotate(frontwheeltheta, 0, 1, 0);
    frontleftwheel_speed_->Rotate(frontwheeltheta, 0, 1, 0);

    // Reset rotation
#if 1
    double alpha_increment = -alpha_ * dt;
    alpha_ += alpha_increment;
    frontleftwheel_direction_->Rotate(alpha_increment, 0, 0, 1);
    frontrightwheel_direction_->Rotate(alpha_increment, 0, 0, 1);
    double steering_rotation = kSteeringWheelIncrement / kAlphaIncrement;
    steering_wheel_->Rotate(alpha_increment * steering_rotation,
                            -.7935, 0, .6085);
#endif
}

