//
// Created by Minh Nguyen on 12/1/2022.
//

#include "control.h"
#include "pid.h"
#include <Arduino.h>

// environmental constants
constexpr float WHEEL_DIAMETER = 0.07f;   // in m
constexpr float AXLE_RADIUS = 0.06f;   // in m
constexpr int TARGET_PER_CYCLE = 280;     // turn the wheel full round with this target

enum class Stage {
    ROTATING,
    ADVANCING,
    IDLE,
};

// state machine
static Stage stage_ = Stage::IDLE;
static float radian_ = 0.0f;
static float distance_ = 0.0f;

// variables

// private methods
void rotate();

void advance();

bool validDistance(float d);

bool ctr::ready() {
    return stage_ == Stage::IDLE;
}

void ctr::loop(const bool debug) {
    switch (stage_) {
        case Stage::ROTATING:
            pid::loop(debug);
            if (pid::ready()) {
                radian_ = 0.0f;
                advance();
            }
            break;
        case Stage::ADVANCING:
            pid::loop(debug);
            if (pid::ready()) {
                distance_ = 0.0f;
                stage_ = Stage::IDLE;
            }
            break;
        case Stage::IDLE:
            break;
    }
}

void ctr::process(const float distance, const float degree) {
    if (validDistance(distance)) {
        const float raw = degree / 180;                     // convert to radian
        const int ratio = static_cast<int>(degree) / 360;   // normalize radian to prevent multiple rotations
        const double radian = (raw > 0) ? (raw - 2 * ratio) * PI : (raw + 2 * ratio) * PI;
        distance_ = distance;
        // scale radian back to [-Pi; Pi]
        if (radian > PI) {
            radian_ = static_cast<float>(radian - 2 * PI);
        } else if (radian < -PI) {
            radian_ = static_cast<float>(radian + 2 * PI);
        } else {
            radian_ = static_cast<float>(radian);
        }
        rotate();
    }
}

bool validDistance(const float d) {
    // distance should be larger than the minimum torque over which the motor cannot turn the wheel
    static const float minDist = (pid::MIN_ERROR * WHEEL_DIAMETER * PI) / TARGET_PER_CYCLE;
    // also it should not exceed the maximum allowed distance that results in overflown torque value
    static const float maxDist = (pid::MAX_TORQUE * WHEEL_DIAMETER * PI) / TARGET_PER_CYCLE;
    return d > minDist && d < maxDist;
}

// expect radian to be from -Pi to Pi
void rotate() {
    const float arc = AXLE_RADIUS * radian_;
    const double target = (arc / (WHEEL_DIAMETER * PI)) * TARGET_PER_CYCLE;
    pid::start(static_cast<int>(target), true);
    stage_ = Stage::ROTATING;
}

void advance() {
    const double target = (distance_ / (WHEEL_DIAMETER * PI)) * TARGET_PER_CYCLE;
    pid::start(static_cast<int>(target));
    stage_ = Stage::ADVANCING;
}