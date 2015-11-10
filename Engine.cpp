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


Engine::Engine(JeepNode jeep, JeepNode frontleftwheel,
        JeepNode frontrightwheel, JeepNode steering_wheel) :
    jeep_(jeep),
    frontleftwheel_(frontleftwheel),
    frontrightwheel_(frontrightwheel),
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

            frontleftwheel_->Translate(2.5, 0.644, 0.438);
            frontleftwheel_->Rotate(kAlphaIncrement, 0, 0, 1);
            frontleftwheel_->Translate(-2.5, -0.644, -0.438);

            frontrightwheel_->Translate(2.5, -0.644, 0.438);
            frontrightwheel_->Rotate(kAlphaIncrement, 0, 0, 1);
            frontrightwheel_->Translate(-2.5, 0.644, -0.438);

            steering_wheel_->Translate(1.111, 0.495, 1.372);
            steering_wheel_->Rotate(kSteeringWheelIncrement,
                    -0.7935, 0, 0.6085);
            steering_wheel_->Translate(-1.111, -0.495, -1.372);
            break;
        case 'd':
            if (alpha_ <= -kAlphaMax)
                break;

            alpha_ = alpha_ - kAlphaIncrement;

            frontleftwheel_->Translate(2.5, 0.644, 0.438);
            frontleftwheel_->Rotate(-kAlphaIncrement, 0, 0, 1);
            frontleftwheel_->Translate(-2.5, -0.644, -0.438);

            frontrightwheel_->Translate(2.5, -0.644, 0.438);
            frontrightwheel_->Rotate(-kAlphaIncrement, 0, 0, 1);
            frontrightwheel_->Translate(-2.5, 0.644, -0.438);

            steering_wheel_->Translate(1.111, 0.495, 1.372);
            steering_wheel_->Rotate(-kSteeringWheelIncrement,
                    -0.7935, 0, 0.6085);
            steering_wheel_->Translate(-1.111, -0.495, -1.372);
            break;
    }
}

void Engine::Update() {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    float dt = (curr_time - last_time_) / 1000.0f;
    last_time_ = curr_time;

    jeep_->Translate(dt * speed_, 0, 0);
}

