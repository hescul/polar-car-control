//
// Created by Minh Nguyen on 11/30/2022.
//

#include <Arduino.h>
#include "pid.h"
#include "encoder.h"
#include "motor.h"

// =========== Principle ===========
// u(t) = kp * e(t) + ki * integral[e(t).dt] + kd * de/dt
// integral[e(t).dt] ~ eIntg + e * deltaT
// de/dt ~ (e - ePrev) deltaT
// ==================================

// PID constants
static constexpr auto kp = 1.0f;
static constexpr auto ki = 0.0f;
static constexpr auto kd = 0.025f;    // prevent overshoot

// keep track of pid variables between calculating iterations
static long prevT_ = 0l;    // for computing delta T
static float ePrev_ = 0.0f;  // for computing delta error
static float eIntg_ = 0.0f;  // estimates integral of error

// states
enum class State {
    IDLE,
    WORKING,
};
static State state_ = State::IDLE;
static int target_ = 0;
static bool inverse_ = false;

void reset() {
    prevT_ = 0l;
    ePrev_ = 0.0f;
    eIntg_ = 0.0f;
    target_ = 0;
    inverse_ = false;
    state_ = State::IDLE;
}

int avgPos() {
    return enc::getPos(Wheel::RIGHT);
}

bool pid::ready() {
    return state_ == State::IDLE;
}

void pid::start(const int target, const bool inverse) {
    if (target != avgPos()) {
        target_ = target;
        inverse_ = inverse;
        state_ = State::WORKING;
    }
}

void pid::loop(const bool debug) {
    if (state_ == State::WORKING) {
        // delta T
        const long currT = static_cast<long>(micros());
        const auto deltaT = static_cast<float>((static_cast<float>(currT - prevT_)) / 1.0e6);
        prevT_ = currT;

        // error term (try swapping the sign if the algorithm is not working)
        const int e = target_ - avgPos();

        // derivative
        const float devt = (e - ePrev_) / deltaT;

        // integral
        eIntg_ += e * deltaT;

        // control signal
        const float u = kp * e + ki * eIntg_ + kd * devt;

        // motor power
        auto pwr = static_cast<float>(fabs(static_cast<double>(u)));
        if (pwr > 255) {
            pwr = 255;
        }

        // motor direction
        Direction dirLft;
        Direction dirRgt;
        if (u > 0 && !inverse_) {   // advance
            dirLft = Direction::FORWARD;
            dirRgt = Direction::FORWARD;
        } else if (u > 0) {         // turn left
            dirRgt = Direction::FORWARD;
            dirLft = Direction::BACKWARD;
        } else if (!inverse_) {     // decede
            dirRgt = Direction::BACKWARD;
            dirLft = Direction::BACKWARD;
        } else {                    // turn right
            dirRgt = Direction::BACKWARD;
            dirLft = Direction::FORWARD;
        }

        if (abs(e) <= MIN_ERROR) {
            dirLft = Direction::STATIC;
            dirRgt = Direction::STATIC;
            pwr = 0;
        }

        // signal motor
        mtr::turn(Wheel::RIGHT, dirRgt);
        mtr::turn(Wheel::LEFT, dirLft);
        mtr::power(static_cast<int>(pwr));

        // store previous error
        ePrev_ = e;

        if (debug) {
            Serial.print(target_);
            Serial.print("\t");
            Serial.print(avgPos());
            Serial.println();
        }

        // reset states when reached the target
        if (dirLft == Direction::STATIC) {
            enc::reset();
            reset();
        }
    }
}
